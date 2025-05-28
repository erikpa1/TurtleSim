use crate::entities::prelude::*;

use super::stepper::Stepper;

pub struct World {
    pub entities: HashMap<String, String>,
    pub stepper: Stepper,
}

impl World {
    pub fn new() -> World {
        World {
            entities: HashMap::new(),
            stepper: Stepper::new(),
        }
    }

    pub fn get_world_info(&self) -> String {
        String::from("This is some world")
    }

    pub fn step(&mut self) {}
}
