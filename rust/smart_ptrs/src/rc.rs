use crate::cell::Cell;
use std::ptr::NonNull;
use std::marker::PhantomData;

// The reason for this structure is because we need to group value and size
// together on heap so count is changed for all threads not just for local one
struct RcInner<T> {
    value: T,
    refcounts: Cell<usize>,
}

// Real Rc actually also support Unsized generic parameters
pub struct Rc<T> {
    // The value needs to points to value on heap since stack for specific
    // thread might go out of scope
    //inner: *const RcInner<T>,
    inner: NonNull<RcInner<T>>,
    // see https://doc.rust-lang.org/nomicon/phantom-data.html
    // PhantomData tells the compiler that we own the RcInner
    _marker: PhantomData<RcInner<T>>,
}

impl<T> Rc<T> {
    pub fn new(value: T) -> Self {
        let inner = Box::new(RcInner {
            value,
            refcounts: Cell::new(1),
        });

        // Why not just `&*inner`, we cannot drop the box since then
        // it deallocates, and compiler will not recognize this
        Self {
            // Box does not give as a null pointer
            inner: unsafe { NonNull::new_unchecked(Box::into_raw(inner)) },
            _marker: PhantomData,
        }
    }
}

impl<T> Clone for Rc<T> {
    fn clone(&self) -> Self {
        let inner = unsafe { &*self.inner.as_ref() };
        let count = inner.refcounts.get();
        inner.refcounts.set(count + 1);

        Rc { inner: self.inner, _marker: PhantomData }
    }
}

impl<T> std::ops::Deref for Rc<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        // self.inner is a Box that is only deallocated when the last rc goes away.
        // we have an Rc, therefore the Box has not been deallocated and deref is fine.
        &unsafe { &*self.inner.as_ref() }.value
    }
}

impl<T> Drop for Rc<T> {
    fn drop(&mut self) {
        let inner = unsafe { &*self.inner.as_ref() };
        let c = inner.refcounts.get();
        if c == 1 {
            // to disable the  usage of inner later on
            drop(inner);
            // It is safe to drop the value since this is the only reference alive
            //dropping inner
            let _ = unsafe { Box::from_raw(self.inner.as_ptr()) };
        } else {
            // there are other Rcs, so don't drop
            inner.refcounts.set(c - 1);
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn bad() {
        let (y, x);
        x = String::from("sasa");
        y = Rc::new(&x);

    }

}
