#include <SFML/Window.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "Cue.hpp"
#include "Ball.hpp"

Cue::Cue()
{
    this->pos_x = 0;
    this->pos_y = 0;
    this->angle = 0;
    this->isVisible = true;
    this->isAnimationOn = false;
}

Cue::Cue(double pos_x, double pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->angle = 0;
    this->isAnimationOn = false;
}

double Cue::getX()
{
    return this->pos_x;
}

double Cue::getY()
{
    return this->pos_y;
}

double Cue::getAngle()
{
    return this->angle;
}

void Cue::setX(double x)
{
    this->pos_x = x;
}

void Cue::setY(double y)
{
    this->pos_y = y;
}

void Cue::startAnimation()
{
    this->isAnimationOn = true;
    this->animationClock = sf::Clock::Clock();
    this->animationClock.restart();
}

void Cue::makeVisible()
{
    this->isVisible = true;
}

void Cue::makeInvisible()
{
    this->isVisible = false;
}

void Cue::Draw(sf::RenderWindow* window)
{
    if(!this->isVisible)
        return;
    sf::Texture texture;
    texture.loadFromFile("Textures/cue.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(this->pos_x, this->pos_y);
    sprite.setRotation(this->angle); //0 = left, 90 = up, 180 = right, 270 = down
    sprite.setScale(0.2, 0.2);
    window->draw(sprite);
}

void Cue::Update(sf::RenderWindow* window, Ball* cue_ball, bool justDoIt)//just updating position based on ball #0 and mouse
{
    sf::Vector2i new_coord = sf::Mouse::getPosition();
    sf::Vector2i mouse = sf::Vector2i(new_coord.x - window->getPosition().x - 15, new_coord.y - window->getPosition().y - 50);
    sf::Vector2f ball(cue_ball->getX()+20, cue_ball->getY()+20);
    double a = (mouse.y - ball.y)/(mouse.x - ball.x);

    double angle = atan(a);
    double x = 60*cos(angle);
    double y = 60*sin(angle);
    this->angle = 180*angle/3.14159265359;
    if(mouse.x < ball.x)
    {
        x *= -1;
        y *= -1;
        this->angle += 180;
    }
    this->pos_x = ball.x + x;
    this->pos_y = ball.y + y;
}

void Cue::Update(sf::RenderWindow* window, Ball* cue_ball)//general Update, including animation and hitting
{
    printf("TIME = %I64d \n", this->animationClock.getElapsedTime().asMicroseconds());
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->Update(window, cue_ball, true);
    }
    if(this->isAnimationOn)
    {
        if( this->animationClock.getElapsedTime().asMicroseconds() >= 0 )
        {
            double percentOfAnimation = (double)this->animationClock.getElapsedTime().asMicroseconds()/1000000;
            sf::Vector2f ball(cue_ball->getX()+20, cue_ball->getY()+20);
            double force = 200;
            double angle;
            if (this->getAngle() <= 180)
                angle = (this->getAngle()*3.14159265359)/180;
            else
                angle = ((this->getAngle() - 180)*3.14159265359)/180;
            double x = force*cos(angle);
            double y = force*sin(angle);
            printf("PERC = %f \n", percentOfAnimation);
            x *= percentOfAnimation;
            y *= percentOfAnimation;
            sf::Vector2f originalPosition;
            if(this->getX() < ball.x && this->getY() < ball.y)
            {
                x *= -1;
                y *= -1;
                originalPosition = sf::Vector2f(ball.x -60*cos(angle), ball.y -60*sin(angle));
            }
            else
            {
                originalPosition = sf::Vector2f(ball.x + 60*cos(angle), ball.y + 60*sin(angle));
            }
            this->setX(originalPosition.x + x);
            this->setY(originalPosition.y + y);
        }
        if( this->animationClock.getElapsedTime().asMicroseconds() >= 1000000)
        {
            double percentOfAnimation = (double)(this->animationClock.getElapsedTime().asMicroseconds() - 1000000)/300000;
            percentOfAnimation = 1 - percentOfAnimation;
            sf::Vector2f ball(cue_ball->getX()+20, cue_ball->getY()+20);
            double force = 200;
            double angle;
            if (this->getAngle() <= 180)
                angle = (this->getAngle()*3.14159265359)/180;
            else
                angle = ((this->getAngle() - 180)*3.14159265359)/180;
            double x = force*cos(angle);
            double y = force*sin(angle);
            printf("PERC = %f \n", percentOfAnimation);
            x *= percentOfAnimation;
            y *= percentOfAnimation;
            sf::Vector2f edgeOfBall;
            if(this->getX() < ball.x && this->getY() < ball.y)
            {
                x *= -1;
                y *= -1;
                edgeOfBall = sf::Vector2f(ball.x + -20*cos(angle), ball.y + -20*sin(angle));
            }
            else
            {
                edgeOfBall = sf::Vector2f(ball.x + 20*cos(angle), ball.y + 20*sin(angle));
            }
            this->setX(edgeOfBall.x + x);
            this->setY(edgeOfBall.y + y);
        }
        if( this->animationClock.getElapsedTime().asMicroseconds() >= 1300000)
        {
            this->Hit(window, cue_ball);
            this->isAnimationOn = false;
        }
    }
}

// double animationFunction(double percOfAnimation)
// {
//     return 
// }

void Cue::Hit(sf::RenderWindow* window, Ball* cue_ball)
{
    double force = 300;
    sf::Vector2f ball(cue_ball->getX()+20, cue_ball->getY()+20);
    double a = (this->pos_y - ball.y)/(this->pos_x - ball.x);
    double angle = atan(a);
    double x = force*cos(angle);
    double y = force*sin(angle);
    if(this->pos_x > ball.x)
    {
        x *= -1;
        y *= -1;
    }
    cue_ball->setVelocity(sf::Vector2f(x, y));
}