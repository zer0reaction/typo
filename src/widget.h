#pragma once
#include <SFML/Graphics.hpp>


class widget {
public:
    virtual void draw_widget(sf::RenderWindow &window) = 0;
};
