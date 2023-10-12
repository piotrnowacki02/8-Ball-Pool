#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#pragma once

class Pot
{
    private:
        double pos_x;
        double pos_y;
    public:
        Pot();
        Pot(double x, double y);

        //gettery
        double getPosX();
        double getPosY();

        void Draw(sf::RenderWindow* window);

};