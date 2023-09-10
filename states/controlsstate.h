#ifndef CONTROLSSTATE_H
#define CONTROLSSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "../entities/button.h"

class ControlsState : public State {
    private:
    
        Button* _menu;
        sf::View _view;
        sf::Font _font;
        sf::Text _title;
        sf::Text _instructionsp1;
        sf::Text _instructionsp2;
        sf::Text _instructions3;
        sf::Text _instructions4;
    
    public:

        ControlsState(StateManager*);
        ~ControlsState();

        virtual void draw(float);
        virtual void handleInput(float);

        sf::View letterBox(sf::View, int, int);

};

#endif