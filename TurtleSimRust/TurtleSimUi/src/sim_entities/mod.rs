
use bevy::prelude::{Plugin, Startup, PostStartup};

pub mod buffer;
pub mod station;


pub struct SimEntitiesPlugin {

}

impl Plugin for SimEntitiesPlugin {
    fn build(&self, app: &mut bevy::prelude::App) {
        app.add_systems(Startup, station::SpawnSimStations);
        app.add_systems(PostStartup, station::PrintSimStations);
    }
}