#include <SFML/Graphics.hpp>
#include "startstate.h"
#include "playstate.h"
#include "controlsstate.h"

#include <iostream>

StartState::StartState(StateManager* sman) 
{
    manager = sman;

    sf::Vector2f pos(1200.f, 800.f);
    _view.setSize(pos);
    pos *= 0.5f;
    _view.setCenter(pos);
    _view = letterBox(_view, manager->window.getSize().x, manager->window.getSize().y);

    _title.setString("PONG");
    _title.setFillColor(sf::Color::White);
    _title.setCharacterSize(140);

    if (!_font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _title.setFont(_font);
    _title.setOrigin(_title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);
    pos.y -= 225;
    _title.setPosition(pos);

    pos.y += 250;
    _button1p = new Button("1 Player", pos);
    pos.y += 100;
    _button2p = new Button("2 Player", pos);
    pos.y += 100;
    _controls = new Button("Controls", pos);
}

StartState::~StartState() 
{
    delete _button1p;
    _button1p = nullptr;

    delete _button1p;
    _button2p = nullptr;

    delete _controls;
    _controls = nullptr;
}

void StartState::draw(float dt)
{
    manager->window.setView(_view);
    manager->window.clear(sf::Color::Black);
    manager->window.draw(_button1p->getText());
    manager->window.draw(_button2p->getText());
    manager->window.draw(_controls->getText());
    manager->window.draw(_title);
 
    return;
}

void StartState::handleInput(float dt) 
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
        
        
        if (_button1p->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {
            manager->changeState(new PlayState(manager, false));
            return;
        }
        if (_button2p->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {
            manager->changeState(new PlayState(manager, true));
            return;
        }
        if (_controls->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {
            manager->changeState(new ControlsState(manager));
            return;
        }

   return;
}

sf::View StartState::letterBox(sf::View view, int windowWidth, int windowHeight)
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
