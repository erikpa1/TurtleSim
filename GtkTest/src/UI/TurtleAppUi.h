//
// Created by Erik Palencik on 29/12/2025.
//

#pragma once

#include <gtk/gtk.h>


namespace turtleui {
    class TurtleAppUi {

    public:
        GtkApplication *_app;
        GtkWidget *_window;

    public:
        TurtleAppUi();
};


}


