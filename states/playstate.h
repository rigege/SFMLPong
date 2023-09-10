#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "../entities/ball.cpp"
#include "../entities/player.cpp"
#include "../entities/wall.cpp"

class PlayState : public State {
    private:
    
        sf::View _view;
        sf::Text _ltext;
        sf::Text _rtext;
        sf::Font font;
        int lpoints;
        int rpoints;
        int bounces;
        bool toright;
        bool multiplayer;
    
    public:

        PlayState(StateManager*, bool);
        ~PlayState();

        Ball* ball;
        Player* p1;
        Player* p2;
        Wall* wall;
    
        virtual void draw(float);
        virtual void handleInput(float);

        void changeDir();

        void updateScore();

        void toEnd();

        sf::View letterBox(sf::View, int, int);

};

#endif