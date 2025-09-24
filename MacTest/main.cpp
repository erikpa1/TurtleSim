#include <SFML/Graphics.hpp>

#include "TurtleSim/Prelude.h"
#include "TurtleSimUI/SimUI.h"

int main()
{
    // SFML 3.0: VideoMode constructor takes Vector2u

    TurtleSim::SimWorld world;
    world.Start();

    TurtleSimUI::SimUI ui;
    ui.Start();


    return 0;
}
