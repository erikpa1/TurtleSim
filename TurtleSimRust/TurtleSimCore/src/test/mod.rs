use crate::entities::*;
use crate::entities::*;

pub fn run_test_1() {
    let mut world = World::new();

    for i in 0..world.stepper.End {
        world.step();

        println!("Doing step: {}/{}", i, world.stepper.End);
    }
}
