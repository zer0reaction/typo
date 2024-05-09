#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>


class word_list {
private:
    std::vector<std::string> words;

public:
    word_list(std::string file_path);

    std::string get_random_word();
};
