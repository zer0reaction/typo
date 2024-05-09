#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "textbox.h"
#include "word_list.h"


#define MAIN_WINDOW_WIDTH 640
#define MAIN_WINDOW_HEIGHT 480
#define FONT_SIZE 50
#define CHARACTER_SPACING 30


// Some main window settings
void set_main_window_settings(sf::RenderWindow &main_window, textbox &main_textbox) {
    main_window.setFramerateLimit(60);

    main_textbox.set_font("fonts/hack.ttf", FONT_SIZE, CHARACTER_SPACING);
    main_textbox.set_cursor_position(0);
    main_textbox.set_cursor_thickness(2);
}


// Marks the errors in red 
int check_spelling(std::string &input_text, std::string &random_word, std::string &color_specification) {
    color_specification = std::string(random_word.length(), 'b'); 
    int errors_count = 0;

    if(input_text.length() <= random_word.length()) {
        for(int i = 0; i < input_text.length(); i++) {
            if(input_text[i] == random_word[i]) color_specification[i] = 'n';
            else {
                color_specification[i] = 'e';
                errors_count += 1;
            }
        }

    } else {
        for(int i = 0; i < random_word.length(); i++) {
            if(input_text[i] == random_word[i]) color_specification[i] = 'n';
            else {
                color_specification[i] = 'e';
                errors_count += 1;
            }
        }

        for(int i = random_word.length(); i < input_text.length(); i++) {
            color_specification += 'e';
            errors_count += 1;
        }
    }

    return errors_count;
}


// To combine two stings for output in a textbox: abc + asdwas = abcwas
std::string merge(std::string input_text, std::string random_word) {
    std::string result;

    if(input_text.length() <= random_word.length()) {
        for(int i = 0; i < input_text.length(); i++) {
            result += input_text[i];
        }
        for(int i = input_text.length(); i < random_word.length(); i++) {
            result += random_word[i];
        }
    }

    else {
        for(int i = 0; i < random_word.length(); i++) {
            result += input_text[i];
        }
        for(int i = random_word.length(); i < input_text.length(); i++) {
            result += input_text[i];
        }
    }


    return result;
}


int main (int argc, char *argv[]) {

    // Setting the window and all the widgets
    sf::RenderWindow main_window(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT), "Typo - learn to type better", sf::Style::Close);
    textbox main_textbox;
    word_list words("words/all.txt");
    set_main_window_settings(main_window, main_textbox);
    std::vector<int> typos(26, 0);

    // Declaring stuff
    std::string input_text, random_word, merged, color_specification;
    int words_per_test = 1;

    // Lambda to replace the current word/s with new word/s
    auto new_word = [&]() {
        input_text = "";
        random_word = "";

        for(int i = 0; i < words_per_test; i++)
            if(i != words_per_test - 1)
                random_word += words.get_random_word() + " ";
            else random_word += words.get_random_word();

        merged = merge(input_text, random_word);
        color_specification = std::string(random_word.length(), 'b');

        main_textbox.set_position((MAIN_WINDOW_WIDTH - merged.length() * CHARACTER_SPACING) / 2.0, 
                (MAIN_WINDOW_HEIGHT - FONT_SIZE) / 2);
    };


    new_word();


    // Loop of the app
    sf::Event event;

    while(main_window.isOpen()) {
        while(main_window.pollEvent(event)) {

            // If the user tries to close the window
            if(event.type == sf::Event::Closed) main_window.close();

            // If some text is entered
            if(event.type == sf::Event::TextEntered) {
                char letter_typed = event.text.unicode;

                // If Backspace is pressed
                if(letter_typed == 8) input_text = input_text.substr(0, input_text.length() - 1);

                // If any other key is pressed (from a to z)
                else if(letter_typed >= 97 && letter_typed <= 122) input_text += letter_typed;
            }

        }

        // Changing stuff to represent current state of the input
        merged = merge(input_text, random_word);
        if(check_spelling(input_text, random_word, color_specification) == 0 
                && input_text.length() == random_word.length())
            new_word();
        if(input_text.length() == 0) main_textbox.hide_cursor();
        else main_textbox.show_cursor();

        // Applying changes
        main_textbox.set_text(merged, color_specification);
        main_textbox.set_cursor_position(input_text.length());

        // Drawing and displaying all the widgets
        main_window.clear(sf::Color(50, 52, 55));
        main_textbox.draw_widget(main_window);
        main_window.display();
    }

    
    return 0;
}
