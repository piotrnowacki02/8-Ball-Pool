#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Wall.hpp"
#include "Pot.hpp"

#pragma once

class Table
{
    private:
        double scale;
        Wall walls[6];
        Pot pots[6];
        sf::RectangleShape field;
        sf::RectangleShape frame;
    public:
        //constructors
        Table();
        Table(double scale);

        Wall* getWalls();
        Pot* getPots();

        //drawing
        void Draw(sf::RenderWindow* window);
};