#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#pragma once

class Wall
{
    private:
        double pos_x;
        double pos_y;
        double size_x;
        double size_y;
    public:
        //constructors
        Wall();
        Wall(double pos_x, double pos_y, double size_x, double size_y);

        //gettery
        double getPosX();
        double getPosY();
        double getSizeX();
        double getSizeY();

        //drawing
        void Draw(sf::RenderWindow* window);
};