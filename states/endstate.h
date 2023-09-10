#ifndef ENDSTATE_H
#define ENDSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "../entities/button.h"

class EndState : public State {
    private:
    
        Button* _replay;
        Button* _menu;
        sf::View _view;
        sf::Font _font;
        sf::Text _title;
        bool _multiplayer;
    
    public:

        EndState(StateManager*, bool, int, int);
        ~EndState();

        virtual void draw(float);
        virtual void handleInput(float);

        sf::View letterBox(sf::View, int, int);

};

#endif