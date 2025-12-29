use bevy::prelude::{Commands, Component, Query};

#[derive(Component)]
pub struct SimStation {
    name: String
}


pub fn SpawnSimStations(mut commands: Commands) {
    commands.spawn( SimStation{
        name: "Obrabacia stanica".to_string()
    });
    commands.spawn( SimStation{
        name: "Pila".to_string()
    });

    commands.spawn( SimStation{
        name: "Freza".to_string()
    });
}

pub fn PrintSimStations(entitiesQuery: Query<&SimStation>) {
    for station in entitiesQuery.iter() {
        println!("Workcenter: {}", station.name);
    }
}