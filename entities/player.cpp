#include <SFML\Graphics.hpp>
#include "player.h"
 
#include <iostream>

Player::Player(int playernum)
{
    _height = 110.f;
    _sprite = sf::RectangleShape(sf::Vector2f(6.f,_height));
    _pnum = playernum;
    velocity = 0.f;
    acceleration = 0.003;

    if (playernum == 1) _sprite.setPosition(0.f, 400-_height/2);
    else _sprite.setPosition(1194.f, 400-_height/2);
    
    position = _sprite.getPosition();
}

sf::RectangleShape Player::getSprite() 
{
    return _sprite;
}

void Player::updatePos() 
{
    position = _sprite.getPosition();
    return;
}

int Player::checkInputs(float dt) 
{
    int code = 0;
        if (_pnum == 1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && position.y > 0){
                _sprite.move(0,velocity*dt);
                code += 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && position.y < 800-_height){
                _sprite.move(0,velocity*dt);
                code -= 1;
            }
        }
        
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && position.y > 0){
                _sprite.move(0,velocity*dt);
                code += 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && position.y < 800-_height){
                _sprite.move(0,velocity*dt);
                code -= 1;
            }
        }
        return code;
}

void Player::accelerate(int moved, float dt) 
{
    if (moved > 0) {
        if (velocity > -0.3) velocity -= 0.3;
        if (velocity < 3 && velocity > -3) velocity -= acceleration*dt;
    }

    else if (moved < 0) {
        if (velocity < 0.3) velocity += 0.3;
        if (velocity < 3 && velocity > -3) velocity += acceleration*dt;
    }
    
    else {
        velocity = 0.f;
    }
    return;
}




