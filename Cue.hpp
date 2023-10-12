#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

#pragma once

class Cue
{
    private:
        double pos_x;
        double pos_y;
        double angle;
        bool isVisible;
        bool isAnimationOn;
        sf::Clock animationClock;
    public:
        //Constructor
        Cue();
        Cue(double pos_x, double pos_y);

        //getters
        double getX();
        double getY();
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
        // double animationFunction(double percOfAnimation);
};