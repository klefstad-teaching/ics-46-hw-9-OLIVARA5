#include "ladder.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);  
    int result = RUN_ALL_TESTS();
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    print_word_ladder(generate_word_ladder("marty", "curls", word_list));
    return result;
}