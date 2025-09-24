//
// Created by Erik Palencik on 24/09/2025.
//

#include "SimUI.h"


namespace TurtleSimUI {


void SimUI::Start() {

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(800, 600));

    while (this->Window.isOpen())
    {
        // SFML 3.0: pollEvent() returns std::optional<Event>
        while (const std::optional<sf::Event> event = this->Window.pollEvent())
        {
            // SFML 3.0: Use event->is<>() to check event type
            if (event->is<sf::Event::Closed>())
            {
                this->Window.close();
            }
        }

        this->Window.clear();
        this->Window.draw(shape);
        this->Window.display();
    }
}


}