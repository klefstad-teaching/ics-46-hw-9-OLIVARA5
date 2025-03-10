#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg){
    cout << msg << word1 << " and " << word2 << endl;
}

bool is_adjacent(const string& word1, const string& word2){
    int adjacent = 0;
    if(word1.length() != word2.length()){
        return false;
    }
    for(int i = 0; i < word1; ++i){
        if(word1[i] != word2[i]){
            adjacent++;
        }
        if(adjacent > 1){
            return false;
        }
    }
    return adjacent == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visted;
    visted.insert(begin_word);
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder_queue.back();
        for(const auto&word: word_list){
            if is_adjacent(last_word, word){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}



void load_words(set<string> &word_list, const string& file_name) {
    ifstream in(file_name); 
    if (!in) {
        throw runtime_error("Can't open input file");
    }

    string word;
    while (file >> word) { 
        word_list.insert(word); 
    }

    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word : ladder) {
        cout << word << " ";
    }
}

void verify_word_ladder(){
    set<string> word_list;
    load_word(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

void my_assert(bool e){
    cout << #e << ((e) ? " passed": " failed") << endl;
}