#ifndef STARTSTATE_H
#define STARTSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "../entities/button.h"

class StartState : public State {
    private:
    
        Button* _button1p;
        Button* _button2p;
        Button* _controls;
        sf::View _view;
        sf::Font _font;
        sf::Text _title;
    
    public:

        StartState(StateManager*);
        ~StartState();

        virtual void draw(float);
        virtual void handleInput(float);

        sf::View letterBox(sf::View, int, int);
};

#endif