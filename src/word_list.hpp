#pragma once
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct word {
    std::string s;
    std::vector<double> typo_coef;
};

class word_list {
  private:
    std::vector<word> words;

  public:
    word_list(std::string file_path);

    std::string get_random_word();
    std::vector<word> get_best_for_typo(std::vector<int> &typos, int amount);
};
