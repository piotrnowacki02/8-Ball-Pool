#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#pragma once

class GraphicElement
{
    protected:
        double pos_x;
        double pos_y;
    public:
        GraphicElement();
        GraphicElement(double x, double y);

        double getX();
        double getY();
        double distance(GraphicElement* elem2);
        virtual void Draw(sf::RenderWindow* window)=0;
};