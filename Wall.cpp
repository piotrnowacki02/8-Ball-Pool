#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Wall.hpp"

Wall::Wall()
{
    this->pos_x = 0;
    this->pos_y = 0;
    this->size_x = 10;
    this->size_y = 100;
}

Wall::Wall(double pos_x, double pos_y, double size_x, double size_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->size_y = size_y;
    this->size_x = size_x;
}

double Wall::getPosX()
{
    return this->pos_x;
}

double Wall::getPosY()
{
    return this->pos_y;
}

double Wall::getSizeX()
{
    return this->size_x;
}

double Wall::getSizeY()
{
    return this->size_y;
}

void Wall::Draw(sf::RenderWindow* window)
{
    sf::RectangleShape rec;
    rec.setSize(sf::Vector2f(this->size_x, this->size_y));
    rec.setPosition(sf::Vector2f(this->pos_x ,this->pos_y));
    rec.setFillColor(sf::Color::Color(0,85,0));
    window->draw(rec);
}
