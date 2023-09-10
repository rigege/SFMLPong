#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "../entities/button.h"

class PauseState : public State {
    private:
    
        Button* _resume;
        Button* _menu;
        sf::View _view;
        sf::Font _font;
        sf::Text _title;
    
    public:

        PauseState(StateManager*);
        ~PauseState();

        virtual void draw(float);
        virtual void handleInput(float);

        sf::View letterBox(sf::View, int, int);

};

#endif