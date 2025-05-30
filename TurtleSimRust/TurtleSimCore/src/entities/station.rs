use crate::behaviours::{ActorTakerBehaviour, ProcessBehaviour};
use crate::entities::prelude::*;

use super::world::World;

pub struct Station {
    pub uid: String,
    pub name: String,
    pub process_time: i64,
    pub world: WeakPtr<World>,
}

impl Station {
    pub fn new() -> Station {
        // Make it public if needed
        Station {
            uid: "".into(),
            name: "".into(),
            process_time: 0,
            world: WeakPtr::new_empty(),
        }
    }

    pub fn new_rc() -> Rc<Box<Station>> {
        Rc::new(Box::new(Station::new()))
    }

    // pub fn station_rc_to_anyrc(station: Rc<Box<Station>>) -> RcAny {

    // }
}

//TODO nejakym sposobom naimportovat tento trait
impl ProcessBehaviour for Station {}

impl ActorTakerBehaviour for Station {}
