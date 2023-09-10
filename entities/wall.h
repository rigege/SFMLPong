#ifndef WALL_H
#define WALL_H

#include <SFML\Graphics.hpp>

class Wall {
    private:
        sf::RectangleShape _sprite;
    public:
        Wall();

        float velocity;

        void randVel();

        sf::RectangleShape getSprite();       
};

#endif