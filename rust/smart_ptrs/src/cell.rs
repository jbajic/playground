use std::cell::UnsafeCell;

pub struct Cell<T> {
    value: UnsafeCell<T>,
}

// UnsafeCell aslo implements
// impl<T> !Sync for Cell<T> {}

impl<T> Cell<T> {
    pub fn new(value: T) -> Self {
        Self {
            value: UnsafeCell::new(value),
        }
    }

    pub fn set(&self, value: T) {
        unsafe { *self.value.get() = value };
    }

    pub fn get(&self) -> T
    where
        T: Copy,
    {
        unsafe { *self.value.get() }
    }
}

#[cfg(test)]
mod test {
    use std::thread;

    use super::*;

    #[test]
    fn bad() {
        let x1 = std::sync::Arc::new(Cell::new(32));
        let x2 = x1.clone();

        thread::spawn(move || {
            x1.set(21);
        });
        thread::spawn(move || {
            x2.set(11);
        });
    }
}
