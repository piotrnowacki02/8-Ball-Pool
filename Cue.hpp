#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "GraphicElement.hpp"

#pragma once

class Cue : GraphicElement
{
    private:
        double angle;
        bool isVisible;
        bool isAnimationOn;
        sf::Clock animationClock;
    public:
        //Constructor
        Cue();
        Cue(double pos_x, double pos_y);

        //gettery
        double getAngle();

        //setter
        void setX(double x);
        void setY(double y);
        void startAnimation();


        void makeVisible();
        void makeInvisible();
        void Draw(sf::RenderWindow* window);
        void Hit(sf::RenderWindow* window, Ball* cue_ball);
        void Update(sf::RenderWindow* window, Ball* cue_ball, bool justDoIt);
        void Update(sf::RenderWindow* window, Ball* cue_ball);
};