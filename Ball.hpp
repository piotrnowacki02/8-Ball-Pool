#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Table.hpp"
#include "Wall.hpp"
#include "Pot.hpp"
#include "GraphicElement.hpp"

#pragma once

//radius = 20
class Ball : GraphicElement
{
    private:
        static sf::SoundBuffer ball2ball;

        int number;
        bool visible;
        sf::Vector2f velocity;
    
    public:
        //Constructor
        Ball();
        Ball(int number);
        Ball(int number, double pos_x, double pos_y);
        Ball(int number, double pos_x, double pos_y, sf::Vector2f velocity);

        //gettery
        bool isVisible();
        double getMass();
        double getX();
        double getY();
        sf::Vector2f getVelocity();
        double getVelocityValue();

        //settery
        void setVelocity(sf::Vector2f v);

        //drawing and updating
        void Draw(sf::RenderWindow* window);
        void Update(sf::Time time, Table table);
        void CollisionSound();

        //physical events
        void Collision(Ball* other_ball);
        bool doTheyCollide(Ball* other_ball);
        void collidingWithWalls(Wall walls[6]);
        bool doesItHitTheWall(Wall wall);
        void ballPotted(Pot pots[6]);
        void applyImpulse(sf::Vector2f impulse, sf::Vector2f offset);

        // Sounds
        static void initializeSounds();
};

