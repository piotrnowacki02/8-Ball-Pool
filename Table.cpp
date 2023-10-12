#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Wall.hpp"
#include "Table.hpp"

Table::Table()
{
    this->scale = 1;
    this->field = sf::RectangleShape();
    this->field.setSize(sf::Vector2f(1180, 620));
    this->field.setPosition(sf::Vector2f(40, 40));
    this->field.setFillColor(sf::Color::Color(0,130,0));
    this->frame = sf::RectangleShape();
    this->frame.setSize(sf::Vector2f(1260, 700));
    this->frame.setPosition(sf::Vector2f(0,0));
    this->frame.setFillColor(sf::Color::Color(40,20,0));
    this->walls[0] = Wall(100, 40, 500, 20);
    this->walls[1] = Wall(660, 40, 500, 20);
    this->walls[2] = Wall(100, 640, 500, 20);
    this->walls[3] = Wall(660,640, 500, 20);
    this->walls[4] = Wall(40, 100, 20, 500);
    this->walls[5] = Wall(1200, 100, 20, 500);
    this->pots[0] = Pot(40, 40);
    this->pots[1] = Pot(600, 40);
    this->pots[2] = Pot(40, 600);
    this->pots[3] = Pot(600, 600);
    this->pots[4] = Pot(1160, 40);
    this->pots[5] = Pot(1160, 600);
    
}

Wall* Table::getWalls()
{
    return this->walls;
}

Pot* Table::getPots()
{
    return this->pots;
}

void Table::Draw(sf::RenderWindow* window)
{
    window->draw(this->frame);
    window->draw(this->field);
    for( int i = 0; i < 6; i++)
        this->walls[i].Draw(window);
    for(int i = 0; i < 6; i++)
        this->pots[i].Draw(window);
}



