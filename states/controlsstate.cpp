#include <SFML/Graphics.hpp>
#include "controlsstate.h"
#include "startstate.h"

#include <iostream>

ControlsState::ControlsState(StateManager* sman) 
{
    manager = sman;

    sf::Vector2f pos(1200.f, 800.f);
    _view.setSize(pos);
    pos *= 0.5f;
    _view.setCenter(pos);
    _view = letterBox(_view, manager->window.getSize().x, manager->window.getSize().y);

    _title.setString("Controls");
    _title.setFillColor(sf::Color::White);
    _title.setCharacterSize(90);

    if (!_font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _title.setFont(_font);
    _title.setOrigin(_title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);
    pos.y -= 325;
    _title.setPosition(pos);

    _instructionsp1.setString("Left Player: W/D for up, S/A for down");
    _instructionsp1.setFillColor(sf::Color::White);
    _instructionsp1.setCharacterSize(40);
    _instructionsp1.setFont(_font);
    _instructionsp1.setOrigin(_instructionsp1.getGlobalBounds().width/2, _instructionsp1.getGlobalBounds().height/2);
    pos.y += 175;
    _instructionsp1.setPosition(pos);

    _instructionsp2.setString("Right Player: Up/Right for up, Down/Left for down");
    _instructionsp2.setFillColor(sf::Color::White);
    _instructionsp2.setCharacterSize(40);
    _instructionsp2.setFont(_font);
    _instructionsp2.setOrigin(_instructionsp2.getGlobalBounds().width/2, _instructionsp2.getGlobalBounds().height/2);
    pos.y += 100;
    _instructionsp2.setPosition(pos);

    _instructions3.setString("Press Escape to pause");
    _instructions3.setFillColor(sf::Color::White);
    _instructions3.setCharacterSize(40);
    _instructions3.setFont(_font);
    _instructions3.setOrigin(_instructions3.getGlobalBounds().width/2, _instructions3.getGlobalBounds().height/2);
    pos.y += 100;
    _instructions3.setPosition(pos);

    _instructions4.setString("The ball will speed up if it's taking too long to between hits");
    _instructions4.setFillColor(sf::Color::White);
    _instructions4.setCharacterSize(40);
    _instructions4.setFont(_font);
    _instructions4.setOrigin(_instructions4.getGlobalBounds().width/2, _instructions4.getGlobalBounds().height/2);
    pos.y += 100;
    _instructions4.setPosition(pos);

    pos.y += 125;
    _menu = new Button("Menu", pos);
}

ControlsState::~ControlsState() 
{
    delete _menu;
    _menu = nullptr;
}

void ControlsState::draw(float dt) 
{
    manager->window.setView(_view);
    manager->window.clear(sf::Color::Black);
    manager->window.draw(_title);
    manager->window.draw(_instructionsp1);
    manager->window.draw(_instructionsp2);
    manager->window.draw(_instructions3);
    manager->window.draw(_instructions4);
    manager->window.draw(_menu->getText());
 
    return;
}

void ControlsState::handleInput(float dt) 
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

        if (_menu->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {  
            manager->changeState(new StartState(manager));
            return;
        }

   return;
}

sf::View ControlsState::letterBox(sf::View view, int windowWidth, int windowHeight)
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