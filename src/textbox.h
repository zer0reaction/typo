#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "widget.h"


class textbox : public widget {
private:
    sf::Font font;
    sf::Color normal_color = sf::Color(209, 208, 197);
    sf::Color error_color = sf::Color(202, 71, 77);
    sf::Color blank_color = sf::Color(100, 102, 105);

    int font_size = 30;
    int character_spacing = 16;
    int position_x = 0;
    int position_y = 0;

    int cursor_position = 0;
    int cursor_thickness = 1;
    bool is_cursor_shown = true;
    sf::Color cursor_color = sf::Color(222, 180, 20);

    std::string text = "";
    std::string color_specification = "";

public:
    void set_text(std::string text, std::string color_specification);
    void set_text(std::string text);
    void set_font(std::string font_path, int font_size, int character_spacing);
    void set_position(int x, int y);
    void set_cursor_position(int position);
    void set_cursor_color(sf::Color color);
    void set_cursor_thickness(int thickness);
    void draw_widget(sf::RenderWindow &window) override;
    void show_cursor();
    void hide_cursor();
    void center(int width, int height);
    
    textbox(std::string text, std::string font_path);
    textbox();
};
