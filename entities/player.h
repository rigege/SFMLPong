#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

class Player {
    private:

        sf::RectangleShape _sprite;
        int _pnum;
        float _height;

    public:

        Player(int);

        sf::Vector2f position;
        float velocity;
        float acceleration;

        sf::RectangleShape getSprite();

        void updatePos();

        int checkInputs(float);

        void accelerate(int, float);
        
};

#endif