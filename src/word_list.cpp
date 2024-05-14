#include "word_list.h"
#include <algorithm>


word_list::word_list(std::string file_path) {
    srand(time(NULL));

    std::ifstream fin(file_path);
    if(!fin.is_open()) std::cout << "Error opening file " << file_path << std::endl;

    std::string s;
    fin >> s;
    
    while(!fin.eof()) {
        word w;
        w.s = s;
        w.typo_coef = std::vector<double>(26, 0.0);

        words.push_back(w);
        fin >> s;
    }


    // for the suggested words for typos to be more random
    auto rng = std::default_random_engine {};
    std::shuffle(words.begin(), words.end(), rng);


    // initializing the coefs
    for(int i = 0; i < words.size(); i++) {
        for(int j = 0; j < words[i].s.length(); j++) {
            words[i].typo_coef[words[i].s[j] - 'a']++;
        }

        for(int j = 0; j < 26; j++) {
            words[i].typo_coef[j] /= double(words[i].s.length());
        }
    }
}


std::string word_list::get_random_word() {
    int index = rand() % words.size();

    return words[index].s;
}


std::vector<word> word_list::get_best_for_typo(char typo, int amount) {
    // higher it is = more lag, but better results
    #define BATCH_SIZE 500

    std::vector<word> top;

    // heavy optimization
    // making a subvector of size 100 from our main vector
    int start = rand() % (words.size() - BATCH_SIZE);
    std::vector<word> sub = std::vector<word>(words.begin() + start, words.begin() + start + BATCH_SIZE);

    // comparator magic
    // we sort the all the words in the order of best for current typo
    // this is not efficient and can cause lags, but i don't know how to make it better yet
    auto comp = [&](word l, word r) {
        return l.typo_coef[typo - 'a'] > r.typo_coef[typo - 'a'];
    };

    std::sort(sub.begin(), sub.end(), comp);

    top = std::vector<word>(sub.begin(), sub.begin() + amount);

    return top;
}
