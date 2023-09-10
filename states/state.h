#ifndef STATE_H
#define STATE_H

#include <SFML\Graphics.hpp>
#include "stateManager.h"
 
class State {
    public:

        StateManager* manager;

        virtual ~State(){
            return;
        }
 
        virtual void draw(float dt) = 0;
        virtual void handleInput(float dt) = 0;
        
};

#endif