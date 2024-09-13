pub use std::cell::RefCell;
pub use std::collections::HashMap;
pub use std::rc::{Rc, Weak};

pub use std::any::Any;

pub struct WeakPtr<T> {
    pub ptr: Option<Weak<RefCell<T>>>,
}

impl<T> WeakPtr<T> {
    pub fn new_empty() -> Self {
        WeakPtr { ptr: None }
    }
    // Constructor to create a new WeakPtr
    pub fn new(ptr: Option<Weak<RefCell<T>>>) -> Self {
        WeakPtr { ptr }
    }

    pub fn set_rc(&mut self, another: &Rc<RefCell<T>>) {
        self.ptr = Some(Rc::downgrade(another));
    }

    // Method to upgrade WeakPtr to Rc<RefCell<T>>
    pub fn upgrade(&self) -> Option<Rc<RefCell<T>>> {
        self.ptr.as_ref().and_then(Weak::upgrade)
    }
}
