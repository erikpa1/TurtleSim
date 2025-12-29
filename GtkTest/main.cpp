#include <iostream>
#include <gtk/gtk.h>

#include "Log/Logger.h"
#include "UI/SimEntitiesLibrary.hpp"
#include "UI/TurtleAppUi.h"

static void on_activate(turtleui::TurtleAppUi *app, gpointer user_data) {

    GtkWidget *button;

    // Create a new window
    app->_window = gtk_application_window_new(app->_app);

    tlog::LogI("Window should be created");



    gtk_window_set_title(GTK_WINDOW(app->_window), "GTK4 Example");
    gtk_window_set_default_size(GTK_WINDOW(app->_window), 400, 300);

    // Create a button
    button = gtk_button_new_with_label("Hello, GTK4!");
    gtk_window_set_child(GTK_WINDOW(app->_window), button);

    // Show the window
    gtk_window_present(GTK_WINDOW(app->_window));
}

int main(int argc, char **argv) {

    turtleui::TurtleAppUi ui;

    std::cout << "Hello, World!";

    int status;

    g_signal_connect(ui._app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(ui._app), argc, argv);

    turtleui::FillLibrary(&ui);

    g_object_unref(ui._app);

    return status;
}