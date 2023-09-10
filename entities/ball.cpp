#define _USE_MATH_DEFINES

#include <SFML\Graphics.hpp>
#include "ball.h"
#include <cmath> 

Ball::Ball()
{
    _radius = 8.f;

    _sprite = sf::CircleShape(_radius);
    _sprite.setPosition(600-_radius/2.f,400-_radius/2.f);

    position = _sprite.getPosition();
    speed = 0.4;
    velocity.x = speed;
    velocity.y = 0.f;
    acceleration = 0.05;
}

void Ball::setSprite(sf::CircleShape spr)
{
    _sprite = spr;
    return;
}

sf::CircleShape Ball::getSprite() 
{
    return _sprite;
}

bool Ball::checkPlayerCollision(sf::FloatRect paddle)
{
    if (_sprite.getGlobalBounds().intersects(paddle)) {
        velocity.x *= -1;
        return true;
    }
    return false;
}

bool Ball::checkWallCollision() 
{
    if (velocity.y >= 0) {
        if (position.y >= 800-_radius*2) {
            velocity.y *= -1;
            return true;
        }
    }
    else {
        if (position.y <= 0) {
            velocity.y *= -1;
            return true;
        }
    }
    return false;
}

bool Ball::checkPoint() 
{
    if (position.x >= 1200-_radius || position.x <= 0-_radius) return true;
    return false;
}

void Ball::updatePos() 
{
    position = _sprite.getPosition();
    return;
}

void Ball::move(float dt, float spd)
{
    _sprite.move(velocity.x*dt*spd,velocity.y*dt*spd);
    return;
}

void Ball::getVelFromRads(float radians) 
{
    velocity.x = speed*cos(radians);
    velocity.y = speed*sin(radians);
    return;
}

void Ball::rebound(float vel) 
{
    accelerate();

    float rads;
    if (velocity.y*vel >= 0 || velocity.y/speed < 0.71) rads = atan((velocity.y+vel/2)/velocity.x);

    if (velocity.x < 0) rads += M_PI;

    getVelFromRads(rads);
    return;
}

void Ball::accelerate() 
{
    speed += acceleration;
    return;
}

bool Ball::reset() 
{
    _sprite.setPosition(600-_radius/2.f,400-_radius/2.f);
    speed = 0.4;
    updatePos();

    int seed = std::rand() % 12;
    getVelFromRads((seed*30 + 15)*(M_PI/180));

    if (velocity.x < 0) return false;
    
    return true;
}
