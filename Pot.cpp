#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "Pot.hpp"

Pot::Pot()
{
    this->pos_x = 0;
    this->pos_y = 0;
}
        
Pot::Pot(double x, double y)
{
    this->pos_x = x;
    this->pos_y = y;
}

double Pot::getPosX()
{
    return this->pos_x;
}

double Pot::getPosY()
{
    return this->pos_y;
}

void Pot::Draw(sf::RenderWindow* window)
{
    sf::CircleShape pot = sf::CircleShape();
    pot.setPosition(this->pos_x, this->pos_y);
    pot.setRadius(30);
    pot.setFillColor(sf::Color::Black);
    window->draw(pot);
}