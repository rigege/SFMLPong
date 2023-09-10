#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include "playstate.h"
#include "startstate.h"
#include "pausestate.h"
#include "endstate.h"

PlayState::PlayState(StateManager* sman, bool twop) 
{
    manager = sman;

    bounces = 0;

    lpoints = 0;
    rpoints = 0;

    _ltext.setCharacterSize(60);
    _rtext.setCharacterSize(60);
    _ltext.setFillColor(sf::Color::White);
    _rtext.setFillColor(sf::Color::White);
    _ltext.setString("0");
    _rtext.setString("0");

    if (!font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _ltext.setFont(font);
    _rtext.setFont(font);
    _ltext.setOrigin(_ltext.getGlobalBounds().width/2, 0);
    _rtext.setOrigin(_ltext.getGlobalBounds().width/2, 0);
    _ltext.setPosition(300.f, 50.f);
    _rtext.setPosition(900.f, 50.f);

    ball = new Ball;
    p1 = new Player(1);

    wall = (twop) ? nullptr : new Wall;
    p2 = (twop) ? new Player(2) : nullptr;
    multiplayer = twop;

    sf::Vector2f pos(1200.f, 800.f);
    _view.setSize(pos);
    pos *= 0.5f;
    _view.setCenter(pos);
    _view = letterBox(_view, manager->window.getSize().x, manager->window.getSize().y);

    int seed = std::rand() % 12;

    ball->getVelFromRads((seed*30 + 15)*(M_PI/180));
    toright = (ball->velocity.x < 0) ? false : true;
}

PlayState::~PlayState() 
{
    delete ball;
    ball = nullptr;

    delete p1;
    p1 = nullptr;
    
    delete p2;
    p2 = nullptr;

    delete wall;
    wall = nullptr;
}

void PlayState::draw(float dt)
{
    manager->window.setView(_view);
    manager->window.clear(sf::Color::Black);
    manager->window.draw(ball->getSprite());
    manager->window.draw(p1->getSprite());

    if (multiplayer) manager->window.draw(p2->getSprite());
    else manager->window.draw(wall->getSprite());

    manager->window.draw(_ltext);
    manager->window.draw(_rtext);
 
    return;
}

void PlayState::handleInput(float dt) 
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        manager->pushState(new PauseState(manager));
        return;
    }

    if (bounces > 4) {
        ball->move(dt, 5.f);
        if ((ball->position.x <= 292.f && !toright) || (ball->position.x >= 892.f && toright)) bounces = 0;
    }
    else ball->move(dt, 1.f);

    int lmoved = p1->checkInputs(dt);
    p1->accelerate(lmoved, dt);

    if (multiplayer) {
        int rmoved = p2->checkInputs(dt);
        p2->accelerate(rmoved, dt);
    }
    
    if (ball->checkWallCollision()) bounces += 1;

    if (ball->checkPoint()) {
        updateScore();
        bounces = 0;

        if ((multiplayer && lpoints == 11) || rpoints == 11)  {
            toEnd();
            return;
        }

        toright = (ball->reset()) ? true : false;
    }

    if (toright) {
        if (multiplayer) {
            if (ball->checkPlayerCollision(p2->getSprite().getGlobalBounds())){
                changeDir();
                ball->rebound(p2->velocity);
                bounces = 0;
            }
        }

        else {
            if (ball->checkPlayerCollision(wall->getSprite().getGlobalBounds())){
                updateScore();
                changeDir();
                wall->randVel();
                ball->rebound(wall->velocity);
                bounces = 0;
            }
        }
    }

    else {
        if (ball->checkPlayerCollision(p1->getSprite().getGlobalBounds())){
                changeDir();
                ball->rebound(p1->velocity);
                bounces = 0;
        }
    }

    ball->updatePos();
    p1->updatePos();
    if (multiplayer) p2->updatePos();

    return;
}

void PlayState::changeDir()
{
    toright = !toright;
    return;
}

void PlayState::updateScore() 
{
    if (toright) {
        lpoints += 1;
        _ltext.setString(std::to_string(lpoints));
    }

    else {
        rpoints += 1;
        _rtext.setString(std::to_string(rpoints));
    }

    return;
}

void PlayState::toEnd() 
{
    manager->changeState(new EndState(manager, multiplayer, lpoints, rpoints));   
    return;
}

sf::View PlayState::letterBox(sf::View view, int windowWidth, int windowHeight)
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