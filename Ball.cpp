#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include "Ball.hpp"
#include "Table.hpp"
#include "Pot.hpp"
#include "Wall.hpp"

Ball::Ball()
{
    this->visible = true;
    this->number = 0;
    this->pos_x = 0;
    this->pos_y = 0;
    this->velocity = sf::Vector2f(0,0);
}

Ball::Ball(int number)
{
    this->visible = true;
    this->number = number;
    this->pos_x = 0;
    this->pos_y = 0;
    this->velocity = sf::Vector2f(0,0);
}

Ball::Ball(int number, double pos_x, double pos_y)
{
    this->visible = true;
    this->number = number;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->velocity = sf::Vector2f(0, 0);
}

Ball::Ball(int number, double pos_x, double pos_y, sf::Vector2f velocity)
{
    this->visible = true;
    this->number = number;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->velocity = velocity;
}

double Ball::getMass()
{
    return 1;
}

double Ball::getX()
{
    return this->pos_x;
}

double Ball::getY()
{
    return this->pos_y;
}

sf::Vector2f Ball::getVelocity()
{
    return this->velocity;
}

double Ball::getVelocityValue()
{
    return std::sqrt(std::pow((this->velocity.x),2)+std::pow((this->velocity.y),2));
}

bool Ball::isVisible()
{
    return this->visible;
}

void Ball::setVelocity(sf::Vector2f v)
{
    this->velocity = v;
}

void Ball::Draw(sf::RenderWindow* window)
{
    sf::Texture texture;
    texture.loadFromFile("Textures/"+std::to_string(this->number)+".png");
    sf::Sprite sprite(texture);
    sprite.setPosition(this->pos_x, this->pos_y);
    sprite.setScale(0.2, 0.2);
    window->draw(sprite);
}

// void Ball::CollisionSound()
// {
//     sf::SoundBuffer buffer;
//     if (!buffer.loadFromFile("Sounds/ballCollision.wav"))
//     throw new std::runtime_error("Could not load from file");
//     sf::Sound sound;
//     sound.setBuffer(buffer);
//     sound.play();
// }

void Ball::Update(sf::Time time, Table table)
{
    float time_mil = time.asMicroseconds()/625;
    this->pos_x += ((time_mil*velocity.x)/600);
    this->pos_y += ((time_mil*velocity.y)/600);
    double friction = 1;//(double)time.asMicroseconds()/20000;
    if(this->velocity.x > 0)
        this->velocity.x -= friction;
    else if(this->velocity.x < 0)
        this->velocity.x += friction;

    if( this->velocity.y > 0)
        this->velocity.y -= friction;
    else if( this->velocity.y < 0)
        this->velocity.y += friction;

    if (std::abs(this->velocity.x) <= 2)
        this->velocity.x = 0;
    if (std::abs(this->velocity.y) <= 2)
        this->velocity.y = 0;
    
    this->collidingWithWalls(table.getWalls());
    this->ballPotted(table.getPots());
}

void Ball::Collision(Ball* other_ball)
{
    double distance = std::sqrt(std::pow(this->getX()-other_ball->getX(),2)+std::pow(this->getY()-other_ball->getY(),2));
    //THE OLD WAY
    // double nx = (other_ball->getX() - this->getX())/distance;
    // double ny = (other_ball->getY() - this->getY())/distance;
    // double p = (this->getVelocity().x * nx + this->getVelocity().y * ny - other_ball->getVelocity().x * nx - other_ball->getVelocity().y * ny);
    // this->velocity = sf::Vector2f(this->getVelocity().x - p * nx, this->getVelocity().y - p * ny);
    // other_ball->velocity = sf::Vector2f(other_ball->getVelocity().x + p * nx, other_ball->getVelocity().y + p * ny);
    //
    //THE NEW WAY (PATRYK WAY)
    sf::Vector2f normal;
    normal.x = (other_ball->pos_x - this->pos_x)/distance;
    normal.y = (other_ball->pos_y - this->pos_y)/distance;
    double depth = 40 - distance;//20+20 = 40 radiuses of balls
    sf::Vector2f contact;
    contact.x = this->pos_x + normal.x * 20;//20 = radius
    contact.y = this->pos_y + normal.y *20;


    sf::Vector2f radiusA;
    radiusA.x = contact.x - this->pos_x;
    radiusA.y = contact.y - this->pos_y;
    sf::Vector2f radiusB;
    radiusB.x = contact.x - other_ball->pos_x;
    radiusB.y = contact.y - other_ball->pos_y;

    sf::Vector2f relativeVelocity = other_ball->getVelocity() - this->getVelocity();
    float contactVelocity = relativeVelocity.x * normal.x + relativeVelocity.y*normal.y;

    if(contactVelocity < 0)
    {
        float e = 1;
        float j = -(1.0f + e)* contactVelocity;
        j /= 2;

        sf::Vector2f impulse = j*normal;
        this->applyImpulse(-impulse, radiusA);
        other_ball->applyImpulse(impulse, radiusB);
    }


    // this->applyImpulse(-tangentImpulse, radiusA);
    // other_ball->applyImpulse(tangentImpulse, radiusB); 

}

bool Ball::doTheyCollide(Ball* other_ball)
{
    double sum_of_radii = 20 + 20; // Suma promieni dwóch kul
    // double distance = std::sqrt(std::pow(((this->pos_x + this->velocity.x/30)- (other_ball->getX()+other_ball->getVelocity().x)), 2) + std::pow(((this->pos_y + this->velocity.y/30)- (other_ball->getY()+other_ball->getVelocity().y)), 2));
    double distance = std::sqrt(std::pow((this->pos_x - other_ball->getX()), 2) + std::pow((this->pos_y - other_ball->getY()), 2));

    if (distance <= sum_of_radii)
    {
        // this->CollisionSound();
        return true;
    }
    return false;
}

void Ball::ballPotted(Pot pots[6])
{
    for(int i = 0; i < 6; i++)
    {
        double distance = std::sqrt(std::pow(pots[i].getPosX() - this->pos_x,2) + std::pow(pots[i].getPosY() - this->pos_y,2));
        if(distance < 30)
        {
            this->visible = false;
            this->pos_x = -800 + 50*this->number;
            this->pos_y = -100;
            this->setVelocity(sf::Vector2f(0,0));
            //POTTED!!!!
        }
    }
}

bool Ball::doesItHitTheWall(Wall wall)
{
    sf::Vector2f Circle(this->getX()+20, this->getY()+20);
    sf::Vector2f Rectangle(wall.getPosX()+wall.getSizeX()/2, wall.getPosY()+wall.getSizeY()/2);
    sf::Vector2f CircleDistance(abs(Circle.x - Rectangle.x), abs(Circle.y - Rectangle.y));

    if(CircleDistance.x > (wall.getSizeX()/2 + 20))//20 = radius
        return false;
    if(CircleDistance.y > (wall.getSizeY()/2 + 20))//20 = radius
        return false;

    if(CircleDistance.x <= (wall.getSizeX()/2))
        return true;
    if(CircleDistance.y <= (wall.getSizeY()/2))
        return true;

    double cornerDistance_sq = pow(CircleDistance.x - wall.getSizeX()/2, 2) + pow(CircleDistance.y - wall.getSizeY()/2,2);
    return (cornerDistance_sq <= 400);//400 = 20^2 = r^2
}

void Ball::collidingWithWalls(Wall walls[6])
{
    if((this->doesItHitTheWall(walls[0]) || this->doesItHitTheWall(walls[1])) && this->velocity.y < 0)
    {
        this->velocity.y *= -0.98;
        printf("%d Ball Hit 0,1 wall\n\n", this->number);
    }
    if((this->doesItHitTheWall(walls[2]) || this->doesItHitTheWall(walls[3])) && this->velocity.y > 0)
    {
        this->velocity.y *= -0.98;
        printf("%d Ball Hit 2,3 wall\n\n", this->number);
    }
    if(this->doesItHitTheWall(walls[4]) && this->velocity.x < 0)
    {
        this->velocity.x *= -0.98;
        printf("%d Ball Hit 4 wall\n\n", this->number);
    }
    if(this->doesItHitTheWall(walls[5]) && this->velocity.x > 0)
    {
        this->velocity.x *= -0.98;
        printf("%d Ball Hit 5 wall\n\n", this->number);
    }

}

void Ball::applyImpulse(sf::Vector2f impulse, sf::Vector2f offset)
{
    this->setVelocity(this->getVelocity() + impulse);
    //rotational optional
}