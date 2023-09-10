#include <SFML\Graphics.hpp>
#include "wall.h"

Wall::Wall()
{
    _sprite = sf::RectangleShape(sf::Vector2f(6.f,800));
    _sprite.setPosition(1194.f,0.f);
}

void Wall::randVel() 
{
    int seed = std::rand() % 4000;
    float vel = seed/1000.f;

    velocity = vel - 2;
    return;
}

sf::RectangleShape Wall::getSprite() 
{
    return _sprite;
}