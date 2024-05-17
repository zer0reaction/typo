#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "textbox.h"
#include "word_list.h"


#define MAIN_WINDOW_WIDTH 1000
#define MAIN_WINDOW_HEIGHT 800
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
        for(int i = 0; i < input_text.length(); i++) { result += input_text[i]; }
        for(int i = input_text.length(); i < random_word.length(); i++) { result += random_word[i]; }
    }

    else {
        for(int i = 0; i < random_word.length(); i++) { result += input_text[i]; }
        for(int i = random_word.length(); i < input_text.length(); i++) { result += input_text[i]; }
    }

    return result;
}


// Adding the current typos to a vector
void count_typos(std::string user_input, std::string random_word, std::vector<int> &typos) {
    for(int i = 0; i < user_input.length(); i++) {
        if(i == user_input.length() - 1) {
            if(i > random_word.length() - 1) {
                break;
            }

            if(user_input[i] != random_word[i]) { typos[random_word[i] - 'a']++; }
        }
    }
}


int main (int argc, char *argv[]) {

    // Setting the window and all the widgets
    sf::RenderWindow main_window(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT), 
            "Typo - learn to type better", sf::Style::Default);

    // Widgets
    textbox main_textbox;
    word_list words("words/all.txt");

    // Variables to work with a textbox
    std::string input_text, random_word, merged, color_specification;
    int words_per_test = 1;

    // To store user's typos
    std::vector<int> typos(26, 0);


    // Setting window settings
    set_main_window_settings(main_window, main_textbox);


    // Lambda to replace the current word/s with new word/s
    auto new_word = [&]() {
        input_text = "";
        random_word = "";

        // Getting word/s from our dictionaty and adding them to current string
        std::vector<word> w = words.get_best_for_typo(typos, words_per_test);
        for(int i = 0; i < words_per_test; i++) {
            if(i != words_per_test - 1) { random_word += w[i].s + " "; }
            else random_word += w[i].s;
        }

        // Setting the string for the textbox (to show the typos and the word to write)
        merged = merge(input_text, random_word);
        color_specification = std::string(random_word.length(), 'b');
    };


    // Processed every frame
    auto update_iteration = [&]() {
        // Making both the user input and the current random_word visible
        merged = merge(input_text, random_word);

        // If there are no typos and the whole word is entered, we update the word to a new one
        if(check_spelling(input_text, random_word, color_specification) == 0 
                && input_text.length() == random_word.length())
            new_word();

        // Hiding the cursor if there is no text typed
        if(input_text.length() == 0) main_textbox.hide_cursor();
        else main_textbox.show_cursor();

        // Applying changes to the textbox
        main_textbox.set_text(merged, color_specification);
        main_textbox.set_cursor_position(input_text.length());
        main_textbox.center(main_window.getSize().x, main_window.getSize().y);

        // Drawing and displaying all the widgets
        main_window.clear(sf::Color(50, 52, 55));
        main_textbox.draw_widget(main_window);
        main_window.display();
    };



    // Adding first word
    new_word();


    // Loop of the app
    sf::Event event;
    while(main_window.isOpen()) {

        // While there are some events happening in the window
        while(main_window.pollEvent(event)) {

            // If the user tries to close the window, we close it
            if(event.type == sf::Event::Closed) main_window.close();

            // If some text is entered, we process it
            if(event.type == sf::Event::TextEntered) {

                // Getting the typed letter
                char letter_typed = event.text.unicode;

                // If Backspace is pressed, we delete the last character
                // And then counting the typos
                // Basically checing if the deleted character is a typo
                if(letter_typed == 8) {
                    count_typos(input_text, random_word, typos);
                    input_text = input_text.substr(0, input_text.length() - 1);
                }

                // If any other key is pressed (from a to z), we add it to the input line
                // TODO: add programming stuff (){}[];:+-<> and numbers
                else if(letter_typed >= 97 && letter_typed <= 122) input_text += letter_typed;
            }

            // If the window is resized, we update the view (for things not to stretch)
            if(event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                main_window.setView(sf::View(visibleArea));           
            }
        }

        // Changing stuff to represent current state of the input
        update_iteration();
    }

    
    return 0;
}
