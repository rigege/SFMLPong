#include <SFML/Graphics.hpp>
#include "endstate.h"
#include "startstate.h"
#include "playstate.h"

#include <iostream>

EndState::EndState(StateManager* sman, bool twop, int lscore, int rscore) 
{
    manager = sman;

    _multiplayer = twop;

    sf::Vector2f pos(1200.f, 800.f);
    _view.setSize(pos);
    pos *= 0.5f;
    _view.setCenter(pos);
    _view = letterBox(_view, manager->window.getSize().x, manager->window.getSize().y);

    std::string string;

    if (twop) string = (lscore < rscore) ? "Right Player Wins" : "Left Player Wins";
    else string = "Score: " + std::to_string(lscore);

    _title.setString(string);
    _title.setFillColor(sf::Color::White);
    _title.setCharacterSize(90);

    if (!_font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _title.setFont(_font);
    _title.setOrigin(_title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);
    pos.y -= 175;
    _title.setPosition(pos);

    pos.y += 250;
    _replay = new Button("Replay", pos);
    pos.y += 100;
    _menu = new Button("Menu", pos);
}

EndState::~EndState() 
{
    delete _replay;
    _replay = nullptr;

    delete _menu;
    _menu = nullptr;
}

void EndState::draw(float dt) 
{
    manager->window.setView(_view);
    manager->window.clear(sf::Color::Black);
    manager->window.draw(_title);
    manager->window.draw(_replay->getText());
    manager->window.draw(_menu->getText());
 
    return;
}

void EndState::handleInput(float dt) 
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

        if (_replay->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {
            manager->changeState(new PlayState(manager, _multiplayer));
            return;
        }
        if (_menu->detectHover(manager->window, _view, manager->window.getSize().x, manager->window.getSize().y, 60, 80)) {  
            manager->changeState(new StartState(manager));
            return;
        }

   return;
}

sf::View EndState::letterBox(sf::View view, int windowWidth, int windowHeight)
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