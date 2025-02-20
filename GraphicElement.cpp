#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GraphicElement.hpp"

#pragma once

GraphicElement::GraphicElement()
{
    this->pos_x = 0;
    this->pos_y = 0;
}

GraphicElement::GraphicElement(double x, double y)
{
    this->pos_x = x;
    this->pos_y = y;
}

double GraphicElement::getX()
{
    return this->pos_x;
}

double GraphicElement::getY()
{
    return this->pos_y;
}

double GraphicElement::distance(GraphicElement* elem2)
{
    return std::sqrt(pow(elem2->getX() - this->pos_x, 2) + pow(elem2->getY() - this->pos_y, 2));
}
