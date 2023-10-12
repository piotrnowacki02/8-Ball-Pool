#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Wall.hpp"
#include "Table.hpp"
#include "BallSet.hpp"

BallSet::BallSet()
{
    this->ball[0] = Ball(0, 200, 300, sf::Vector2f(0, 0));
    this->ball[1] = Ball(1, 400, 300, sf::Vector2f(0, 0));
    this->ball[2] = Ball(2, 450, 275, sf::Vector2f(0, 0));
    this->ball[3] = Ball(3, 450, 325, sf::Vector2f(0, 0));
    this->ball[4] = Ball(4, 500, 250, sf::Vector2f(0, 0));
    this->ball[5] = Ball(5, 500, 300, sf::Vector2f(0, 0));
    this->ball[6] = Ball(6, 500, 350, sf::Vector2f(0, 0));
    this->ball[7] = Ball(7, 550, 225, sf::Vector2f(0, 0));
    this->ball[8] = Ball(8, 550, 275, sf::Vector2f(0, 0));

}

Ball* BallSet::getBall(int i)
{
    return &(this->ball[i]);
}

void BallSet::Update(sf::Time time, Table table)
{
    for(int i = 0; i <= 8; i++)
    {
        this->getBall(i)->Update(time, table);
        for(int j = 0; j <= 8; j++)
        {
            if (i == j)
                continue;
            if(this->getBall(i)->doTheyCollide(this->getBall(j)))
            {
                printf("%d + %d collided\n\n", i, j);
                this->getBall(i)->Collision(this->getBall(j));
            }
        }
    }
}

bool BallSet::isSomethingMoving()
{
    for(int i = 0; i <= 8; i++)
    {
        if(this->getBall(i)->getVelocityValue() != 0)
            return true;
    }
    return false;
}

void BallSet::Draw(sf::RenderWindow* window)
{
    for(int i = 0; i <= 8; i++)
    {
        if(this->getBall(i)->isVisible())
            this->getBall(i)->Draw(window);
    }
}