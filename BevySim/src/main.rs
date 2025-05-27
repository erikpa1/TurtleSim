use bevy::prelude::*;

fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_systems(Startup, startup_scripts)
        .add_systems(Startup, print_names)
        .add_systems(Update, hello_world)
        .run();
}

#[derive(Component)]
pub struct Person {
    pub name: String,
}

#[derive(Component)]
struct Position {
    x: f32,
    y: f32,
}

fn print_position_system(query: Query<&Position>) {
    for position in &query {
        println!("position: {} {}", position.x, position.y);
    }
}

fn startup_scripts(mut commands: Commands, asset_server: Res<AssetServer>) {
    commands.spawn(Camera2d);

    commands.spawn(Sprite::from_image(
        asset_server.load("res/textures/vzv.png"),
    ));

    commands.spawn(Person {
        name: String::from("Peter"),
    });

    commands.spawn(Person {
        name: String::from("Maros"),
    });

    commands.spawn(Person {
        name: String::from("Erik"),
    });

    println!("Spawned person!");
}

pub fn print_names(query: Query<&Person>) {
    for person in query.iter() {
        println!("name: {} ", person.name);
    }

    println!("Persons printed")
}

fn hello_world() {
    //println!("hello world!");
}
