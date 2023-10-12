#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Ball.hpp"
#include "BallSet.hpp"
#include "Wall.hpp"
#include "Table.hpp"
#include "Cue.hpp"
#include "Pot.hpp"

#pragma once

class GameSet
{
    private:
        BallSet ballSet;
        Table table;
        Cue cue;
        std::string gameState;
        bool somethingWasMovingBefore;
        int currentPlayer;
        int StripesPlayer;
        int SolidsPlayer;
        int NumberOfSolidLeft;
        int NumbersOfStripesLeft;

    public:
        //constructor
        GameSet();

        //Update and Drawing
        void Update(sf::RenderWindow* window, sf::Time time_elapsed);
        void Draw(sf::RenderWindow* window);

        //Events
        void newTurn();
        

};


