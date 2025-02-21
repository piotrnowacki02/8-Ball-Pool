#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "GraphicElement.hpp"

#pragma once

class Pot
{
    private:
        double pos_x;
        double pos_y;
    public:
        Pot();
        Pot(double x, double y);

        double getX();
        double getY();

        void Draw(sf::RenderWindow* window);

};