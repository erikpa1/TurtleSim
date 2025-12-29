//
// Created by Erik Palencik on 29/12/2025.
//

#pragma once
#include "./TurtleAppUi.h"

namespace turtleui {

    void FillLibrary(TurtleAppUi *app) {

        GtkWidget *button;
        button = gtk_button_new_with_label("Hello, GTK4!");
        gtk_window_set_child(GTK_WINDOW(app->_window), button);


    }
}

