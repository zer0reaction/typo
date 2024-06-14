#include "textbox.h"

#define DEFAULT_FONT_PATH "fonts/hack.ttf"

void textbox::draw_widget(sf::RenderWindow &window) {
    // Drawing characters
    for (int i = 0; i < text.length(); i++) {
        sf::Text character;
        std::string s(1, text[i]);

        character.setFont(font);
        character.setString(s);
        character.setCharacterSize(font_size);
        character.setPosition(position_x + i * character_spacing, position_y);

        if (color_specification[i] == 'e')
            character.setFillColor(error_color);
        if (color_specification[i] == 'n')
            character.setFillColor(normal_color);
        if (color_specification[i] == 'b')
            character.setFillColor(blank_color);

        window.draw(character);
    }

    // Drawing cursor
    if (is_cursor_shown) {
        sf::RectangleShape cursor;
        cursor.setPosition(position_x + cursor_position * character_spacing,
                           position_y);
        cursor.setFillColor(cursor_color);
        cursor.setSize(
            sf::Vector2f(cursor_thickness, font_size + font_size / 5.0));

        window.draw(cursor);
    }
}

void textbox::set_font(std::string font_path, int font_size,
                       int character_spacing) {
    if (!font.loadFromFile(font_path))
        std::cout << "Error loading font " << font_path << std::endl;
    this->font_size = font_size;
    this->character_spacing = character_spacing;
}

void textbox::set_text(std::string text, std::string color_specification) {
    if (text.length() != color_specification.length()) {
        std::cout << "Text and color specification are not the same length! "
                     "Nothing changed. "
                  << text.length() << " " << color_specification.length()
                  << std::endl;
        return;
    }
    this->text = text;
    this->color_specification = color_specification;
}

void textbox::set_text(std::string text) {
    this->text = text;
    this->color_specification = std::string(text.length(), 'n');
}

void textbox::set_position(int x, int y) {
    position_x = x;
    position_y = y;
}

void textbox::set_cursor_position(int position) { cursor_position = position; }

void textbox::show_cursor() { is_cursor_shown = true; }

void textbox::hide_cursor() { is_cursor_shown = false; }

void textbox::set_cursor_color(sf::Color color) { cursor_color = color; }

void textbox::set_cursor_thickness(int thickness) {
    cursor_thickness = thickness;
}

void textbox::center(int width, int height) {
    set_position((width - text.length() * font_size / 2.0) / 2.0,
                 (height - font_size) / 2.0);
}

textbox::textbox(std::string text, std::string font_path) {
    color_specification = std::string(text.length(), 'n');
    set_text(text, color_specification);
    set_font(font_path, font_size, character_spacing);
}

textbox::textbox() {
    set_font(DEFAULT_FONT_PATH, font_size, character_spacing);
}
