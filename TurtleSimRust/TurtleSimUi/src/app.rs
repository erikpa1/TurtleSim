use bevy_egui::egui::Ui;

pub fn DrawApp(  main: &mut Ui) {

    main.with_layout(egui::Layout::right_to_left(egui::Align::TOP), |ui| {
        ui.label("world!");
        ui.label("Hello");
    });

}