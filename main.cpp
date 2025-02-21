#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "Ball.hpp"
#include "BallSet.hpp"
#include "Wall.hpp"
#include "Table.hpp"
#include "Cue.hpp"
#include "Pot.hpp"
#include "GameSet.hpp"
#include "GraphicElement.hpp"

using namespace std;
using namespace sf;

bool closingWindow(RenderWindow* window, Event* event)
{
    while (window->pollEvent(*event))
    {
        if (event->type == Event::Closed)
        {
            window->close();
            return true;
        }
    }
    return false;
}

int main()
{
    sf::Clock clock;
    RenderWindow window{VideoMode{1500, 800}, L"8 Ball Pool"};
    sf::View view = window.getDefaultView();
    window.setFramerateLimit(300);
    Event event;
    GameSet gameSet = GameSet();
    Ball::initializeSounds();
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        window.clear(Color::Color(128,128,128));
        if (closingWindow(&window, &event))
            break;
        gameSet.Update(&window, elapsed);
        gameSet.Draw(&window);

        window.display();
    }
    return 0;
}