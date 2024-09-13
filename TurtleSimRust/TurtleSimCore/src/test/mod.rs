use crate::entities::*;
use crate::entities::*;

impl dyn Entity {
    pub fn interact_with(&self, other: Rc<RefCell<dyn Entity>>) {
        // Example interaction logic
        println!(
            "{} interacts with {}",
            self.get_name(),
            other.borrow().get_name()
        );
    }
}

impl Station {
    pub fn interact_with(&self, other: Rc<RefCell<dyn Entity>>) {
        println!("Here");
    }
}

pub fn run_test_1() {
    let mut world = Rc::new(RefCell::new(World::new()));

    let mut station = Rc::new(RefCell::new(Station::new()));

    {
        let mut station_mut = station.borrow_mut();
        station_mut.name = "Station 1".into();
        station_mut.world.set_rc(&world);
    }

    let buffer = Rc::new(RefCell::new(Station::new()));
    buffer.borrow_mut().name = "Station 2".into();

    let mut tmp_world = world.borrow_mut();
    // Add entities to registry
    tmp_world.add_entity("Station1".to_string(), station.clone());
    tmp_world.add_entity("Station2".to_string(), buffer.clone());

    // Example interaction
    if let Some(station) = tmp_world.get_entity("Station1") {
        if let Some(buffer) = tmp_world.get_entity("Station2") {
            
            station.borrow().interact_with(buffer.clone());

            // let tmp = cast_entity_to::<Station>(&station.borrow());

            station.borrow().as_any().downcast_ref::<Station>().unwrap().interact_with(buffer);

        }
    }

    println!("Finished");
}
