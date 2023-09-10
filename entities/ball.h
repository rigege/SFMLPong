#ifndef BALL_H
#define BALL_H

#include <SFML\Graphics.hpp>

class Ball {
    private:

        sf::CircleShape _sprite;
        float _radius;

    public:

        Ball();
       
        sf::Vector2f position;
        sf::Vector2f velocity;
        float speed;
        float acceleration;

        void setSprite(sf::CircleShape);
        sf::CircleShape getSprite();

        bool checkPlayerCollision(sf::FloatRect);
        bool checkWallCollision();
        bool checkPoint();

        void updatePos();

        void move(float, float);

        void getVelFromRads(float);
        void rebound(float);
        void accelerate();

        bool reset();

};

#endif