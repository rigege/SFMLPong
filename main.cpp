#include <SFML\Graphics.hpp>
#include "states/statemanager.cpp"
#include "states/playstate.cpp"
#include "states/startstate.cpp"
#include "states/pausestate.cpp"
#include "states/endstate.cpp"
#include "states/controlsstate.cpp"

#include "entities/button.cpp"

#include <iostream>

int main() {

    StateManager Manager(1200, 800);
    Manager.pushState(new StartState(&Manager));
    sf::Clock clock;

    while (Manager.window.isOpen()){

        float dt = clock.restart().asMilliseconds();

        if(Manager.getState() == nullptr) {
            Manager.pushState(new StartState(&Manager));
            continue;
        }

        Manager.getState()->handleInput(dt);
        Manager.window.clear(sf::Color::Black);
        Manager.getState()->draw(dt);
        Manager.window.display();
    
    }

    return 0;
}