#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Ball.hpp"
#include "Ball.hpp"
#include "BallSet.hpp"
#include "Wall.hpp"
#include "Table.hpp"
#include "Cue.hpp"
#include "Pot.hpp"
#include "GameSet.hpp"

GameSet::GameSet()
{
    this->ballSet = BallSet();
    this->table = Table();
    this->currentPlayer = 1;
    this->NumberOfSolidLeft = 7;
    this->NumbersOfStripesLeft = 7;
    this->cue = Cue();
    this->gameState = "move";
    this->somethingWasMovingBefore = false;
}



void GameSet::Update(sf::RenderWindow* window, sf::Time time_elapsed)
{
    this->ballSet.Update(time_elapsed, this->table);

    //Updating gamestate, cue visibility etc
    if(!this->ballSet.isSomethingMoving() && this->somethingWasMovingBefore)//everything stopped
    {
        this->newTurn();
        this->somethingWasMovingBefore = false;
        this->cue.Update(window, this->ballSet.getBall(0), true);
    }
    else if(this->ballSet.isSomethingMoving() && !this->somethingWasMovingBefore)//something moved
    {
        this->gameState = "Balls rolling";
        this->somethingWasMovingBefore = true;
        cue.makeInvisible();
    }

    if(this->gameState == "move")
        cue.Update(window, ballSet.getBall(0));
    //hitting animation
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->cue.startAnimation();
    }
}

void GameSet::Draw(sf::RenderWindow* window)
{
    this->table.Draw(window);
    this->ballSet.Draw(window);
    this->cue.Draw(window);
}

void GameSet::newTurn()
{
    this->currentPlayer == 1 ? this->currentPlayer = 2 : this->currentPlayer = 1;
    this->gameState = "move";
    this->cue.makeVisible();
}

