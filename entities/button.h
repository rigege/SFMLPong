#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>

class Button {

    private:

        sf::Font _font;
        sf::Text _text;
        sf::IntRect _bounds;
        float _boundfactor;

    public:

        Button(std::string, sf::Vector2f);

        sf::Text getText();

        void setBoundFactor(int, int);

        sf::Vector2i convertCoords(sf::RenderWindow &, sf::View, int, int);

        bool detectHover(sf::RenderWindow &, sf::View, int, int, int, int);

        bool detectClick();
   
};

#endif