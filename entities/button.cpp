#include <SFML\Graphics.hpp>
#include "button.h"

#include <iostream>

Button::Button(std::string txt, sf::Vector2f centerpos) 
{
    _boundfactor = 1;

    _text.setString(txt);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(60);

    if (!_font.loadFromFile("resources/Roboto-Regular.ttf")) std::cout << "failed to load font";

    _text.setFont(_font);
    _text.setOrigin(_text.getGlobalBounds().width/2, _text.getGlobalBounds().height/2);
    _text.setPosition(centerpos);

    _bounds = (sf::IntRect)_text.getGlobalBounds();

}

sf::Text Button::getText() 
{
    return _text;
}

void Button::setBoundFactor(int windowWidth, int windowHeight) 
{
    float hfactor = windowHeight/800.f;
    float wfactor = windowWidth/1200.f; 

    _boundfactor = std::min(wfactor, hfactor);
    return;
}

sf::Vector2i Button::convertCoords(sf::RenderWindow &window, sf::View view, int sizex, int sizey) 
{
    setBoundFactor(window.getSize().x, window.getSize().y);

    sf::Vector2f fpos = (sf::Vector2f)sf::Mouse::getPosition(window);
    sf::Vector2i coords = (sf::Vector2i)(fpos/_boundfactor);

    if (view.getViewport().getPosition().x) coords.x -= view.getViewport().getPosition().x * sizex / _boundfactor;

    else if (view.getViewport().getPosition().y) coords.y -= view.getViewport().getPosition().y * sizey / _boundfactor;

    return coords;
}

bool Button::detectHover(sf::RenderWindow &window, sf::View view, int sizex, int sizey, int start, int end) 
{
    sf::Vector2i coords = convertCoords(window, view, sizex, sizey);

    if (_bounds.contains(coords)){ 
        if (_text.getCharacterSize() != end) {
            _text.setCharacterSize(end);
            sf::Vector2f moveby(_bounds.getSize().x - _text.getGlobalBounds().getSize().x, _bounds.getSize().y - _text.getGlobalBounds().getSize().y);
            _text.move(moveby*0.5f);
        }

        if (detectClick()) return true;
    }

    else {
        if (_text.getCharacterSize() != start) {
            sf::Vector2f moveby(_text.getGlobalBounds().getSize().x - _bounds.getSize().x, _text.getGlobalBounds().getSize().y - _bounds.getSize().y);
            _text.move(moveby*0.5f);
            _text.setCharacterSize(start);
        }
    }
    return false;
}

bool Button::detectClick() 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return true;
    return false;
}