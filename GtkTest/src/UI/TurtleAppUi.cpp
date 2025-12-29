//
// Created by Erik Palencik on 29/12/2025.
//

#include "TurtleAppUi.h"

#include "../Log/Logger.h"

namespace turtleui {

    TurtleAppUi::TurtleAppUi() {

        tlog::LogI("Before app allocation");
        _app = gtk_application_new("org.turtle.turtlesim", G_APPLICATION_DEFAULT_FLAGS);
        tlog::LogI("After app allocation");

    }
}