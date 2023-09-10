#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML\Graphics.hpp>
#include <stack>

class State;

class StateManager {
    public:

        StateManager(int, int);
        ~StateManager();
        
        std::stack<State *> states;

        sf::RenderWindow window;

        void pushState(State* state);
        void popState();
        void changeState(State* state);
        void resetState(State* state);
        State* getState();
        
};

#endif