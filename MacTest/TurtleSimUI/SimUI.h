//
// Created by Erik Palencik on 24/09/2025.
//

#pragma once



#include <SFML/Graphics.hpp>



namespace TurtleSimUI {
    class SimUI {


      public:
        sf::RenderWindow Window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "SFML Test");



       public:

         void Start();



    };

}


