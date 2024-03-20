use std::cell::UnsafeCell;

use crate::cell::Cell;

#[derive(Copy, Clone)]
enum RefState {
    Unshared,
    Shared(usize),
    Exclusive,
}

pub struct RefCell<T> {
    value: UnsafeCell<T>,
    state: Cell<RefState>,
}

// Implied by UnsafeCell
// impl<T> !Sync for RefCell<T> {}

impl<T> RefCell<T> {
    pub fn new(value: T) -> Self {
        Self {
            value: UnsafeCell::new(value),
            state: Cell::new(RefState::Unshared),
        }
    }

    pub fn borrow(&self) -> Option<Ref<'_, T>> {
        match self.state.get() {
            RefState::Unshared => {
                self.state.set(RefState::Shared(1));
                // No exclusive reference have been given out since state would
                // be Exclusive
                //Some(unsafe { &*self.value.get() })
                Some(Ref { refcell: self })
            }
            RefState::Shared(count) => {
                self.state.set(RefState::Shared(count + 1));
                // No exclusive reference have been given out since state would
                // be Exclusive
                //Some(unsafe { &*self.value.get() })
                Some(Ref { refcell: self })
            }
            RefState::Exclusive => None,
        }
    }

    pub fn borrow_mut(&self) -> Option<RefMut<'_, T>> {
        match self.state.get() {
            RefState::Unshared => {
                self.state.set(RefState::Exclusive);
                // No other references have been give out since state would
                // be Shared or Exclusive
                //Some(unsafe { &mut *self.value.get() })
                Some(RefMut { refcell: self })
            }
            RefState::Shared(_) | RefState::Exclusive => None,
        }
    }
}

/// We need Ref for counting the inner value references when being dropped
pub struct Ref<'refcell, T> {
    refcell: &'refcell RefCell<T>,
}

impl<T> std::ops::Deref for Ref<'_, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        // a Ref is only created if no exclusive references have not been
        // given out.
        //
        // Once given out state is set to shared, so no exclusive references
        // are given out. Dereferencing into shared reference is fine.
        unsafe { &*self.refcell.value.get() }
    }
}

impl<T> Drop for Ref<'_, T> {
    fn drop(&mut self) {
        match self.refcell.state.get() {
            RefState::Unshared | RefState::Exclusive => unreachable!(),
            RefState::Shared(1) => {
                self.refcell.state.set(RefState::Unshared);
            }
            RefState::Shared(n) => {
                self.refcell.state.set(RefState::Shared(n - 1));
            }
        }
    }
}

/// We need Ref for counting the inner value references when being dropped
pub struct RefMut<'refcell, T> {
    refcell: &'refcell RefCell<T>,
}

impl<T> std::ops::Deref for RefMut<'_, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        // a Ref is only created if no exclusive references have not been
        // given out.
        //
        // Once given out state is set to shared, so no exclusive references
        // are given out. Dereferencing into shared reference is fine.
        unsafe { &*self.refcell.value.get() }
    }
}

impl<T> std::ops::DerefMut for RefMut<'_, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        // a RefMut is only created if no references have not been
        // given out.
        //
        // Once given out state is set to exclusive so no references
        // are given out. So dereferencing into exclusive reference is fine
        // since we have an exclusive view into the inner value.
        unsafe { &mut *self.refcell.value.get() }
    }
}

impl<T> Drop for RefMut<'_, T> {
    fn drop(&mut self) {
        match self.refcell.state.get() {
            RefState::Unshared | RefState::Shared(_) => unreachable!(),
            RefState::Exclusive => {
                self.refcell.state.set(RefState::Unshared);
            }
        }
    }
}
