#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Table.hpp"

#pragma once

class BallSet
{
    private:
        Ball ball[9];
    public:
        //Consturctor
        BallSet();
        
        //gettery
        Ball* getBall(int i);

        //updating 
        void Update(sf::Time time, Table table);
        bool isSomethingMoving();

        //drawing
        void Draw(sf::RenderWindow* window);
};


