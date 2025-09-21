#include <SFML/Graphics.hpp>

#include "TurtleSim/Prelude.h"

int main() {
    // SFML 3.0: VideoMode constructor takes Vector2u
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Test");


    TurtleSim::SimWorld world;

    world.Start();


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(800, 600));

    while (window.isOpen()) {
        // SFML 3.0: pollEvent() returns std::optional<Event>
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // SFML 3.0: Use event->is<>() to check event type
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
