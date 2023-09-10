#include <SFML/Graphics.hpp>
#include "pausestate.h"
#include "startstate.h"

#include <iostream>

PauseState::PauseState(StateManager* sman) 
{
    manager = sman;

    sf::Vector2f pos(1200.f, 800.f);
    _view.setSize(pos);
    pos *= 0.5f;
    _view.setCenter(pos);
    _view = letterBox(_view, manager->window.getSize().x, manager->window.getSize().y);

    _title.setString("Paused");
    _title.setFillColor(sf::Color::White);
    _title.setCharacterSize(90);

    if (!_font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _title.setFont(_font);
    _title.setOrigin(_title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);
    pos.y -= 175;
    _title.setPosition(pos);

    pos.y += 250;
    _resume = new Button("Resume", pos);
    pos.y += 100;
    _menu = new Button("Menu", pos);
}

PauseState::~PauseState() 
{    
    delete _resume;
    _resume = nullptr;

    delete _menu;
    _menu = nullptr;
}

void PauseState::draw(float dt) 
{
    manager->window.setView(_view);
    manager->window.clear(sf::Color::Black);
    manager->window.draw(_title);
    manager->window.draw(_resume->getText());
    manager->window.draw(_menu->getText());
 
    return;
}

void PauseState::handleInput(float dt) 
{
    sf::Event event;
    while (manager->window.pollEvent(event)){

            switch(event.type){
                case sf::Event::Closed: 
                    manager->window.close();
                    break;

                case sf::Event::Resized:
                    _view = letterBox(_view, event.size.width, event.size.height);
                    break;               

                default:
                    break;
            }
        }

        if (_resume->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {
            manager->popState();
            return;
        }
        if (_menu->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {  
            manager->resetState(new StartState(manager));
            return;
        }

   return;
}

sf::View PauseState::letterBox(sf::View view, int windowWidth, int windowHeight)
{
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) {
        sizeX = viewRatio/windowRatio;
        posX = (1 - sizeX)/2.f;
    }

    else {
        sizeY = windowRatio/viewRatio;
        posY = (1 - sizeY)/2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;   
}