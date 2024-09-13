
use crate::entities::prelude::*;
use crate::entities::Entity;

pub struct World {
    pub entities: HashMap<String, Rc<RefCell<dyn Entity>>>,
}

impl World {
    pub fn new() -> World {
        World {
            entities: HashMap::new(),
        }
    }

    pub fn add_entity(&mut self, name: String, entity: Rc<RefCell<dyn Entity>>) {
        self.entities.insert(name, entity);
    }

    pub fn get_entity(&self, name: &str) -> Option<Rc<RefCell<dyn Entity>>> {
        self.entities.get(name).cloned()
    }

    pub fn get_world_info(&self) -> String {
        String::from("This is some world")
    }
}
