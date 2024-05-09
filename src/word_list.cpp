#include "word_list.h"


word_list::word_list(std::string file_path) {
    srand(time(NULL));

    std::ifstream fin(file_path);
    if(!fin.is_open()) std::cout << "Error opening file " << file_path << std::endl;

    std::string s;
    fin >> s;
    
    while(!fin.eof()) {
        words.push_back(s);
        fin >> s;
    }
}


std::string word_list::get_random_word() {
    int index = rand() % words.size();
    return words[index];
}
