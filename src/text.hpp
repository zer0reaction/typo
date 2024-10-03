#pragma once

#include <string>

// Marks the errors in red
int check_spelling(std::string &input_text, std::string &random_word,
                   std::string &color_specification) {
    color_specification = std::string(random_word.length(), 'b');
    int errors_count = 0;

    if (input_text.length() <= random_word.length()) {
        for (int i = 0; i < input_text.length(); i++) {
            if (input_text[i] == random_word[i])
                color_specification[i] = 'n';
            else {
                color_specification[i] = 'e';
                errors_count += 1;
            }
        }

    } else {
        for (int i = 0; i < random_word.length(); i++) {
            if (input_text[i] == random_word[i])
                color_specification[i] = 'n';
            else {
                color_specification[i] = 'e';
                errors_count += 1;
            }
        }

        for (int i = random_word.length(); i < input_text.length(); i++) {
            color_specification += 'e';
            errors_count += 1;
        }
    }

    return errors_count;
}

// To combine two stings for output in a textbox: abc + asdwas = abcwas
std::string merge(std::string input_text, std::string random_word) {
    std::string result;

    if (input_text.length() <= random_word.length()) {
        for (int i = 0; i < input_text.length(); i++) {
            result += input_text[i];
        }
        for (int i = input_text.length(); i < random_word.length(); i++) {
            result += random_word[i];
        }
    }

    else {
        for (int i = 0; i < random_word.length(); i++) {
            result += input_text[i];
        }
        for (int i = random_word.length(); i < input_text.length(); i++) {
            result += input_text[i];
        }
    }

    return result;
}

// Adding the current typos to a vector
void count_typos(std::string user_input, std::string random_word,
                 std::vector<int> &typos) {
    for (int i = 0; i < user_input.length(); i++) {
        if (i == user_input.length() - 1) {
            if (i > random_word.length() - 1) {
                break;
            }

            if (user_input[i] != random_word[i]) {
                typos[random_word[i] - 'a']++;
            }
        }
    }
}
