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

int levenshteinAlgorithm(const std::string& str1, const std::string& str2){
    vector<vector<int>> la(str1.length() + 1, vector<int>((str2.length() + 1),0));

    for(size_t i = 0; i <= str1.length(); ++i){
        la[i][0] = i;
    }
    for (size_t j = 0; j <= str2.length(); j++) {
        la[0][j] = j;
    }
 
    for (size_t i = 1; i <= str1.length(); i++) {
        for (size_t j = 1; j <= str2.length(); j++) {
            if (str1[i-1] == str2[j-1]) {
                la[i][j] = la[i-1][j-1];
            } else {
                la[i][j] = 1 + min(la[i-1][j], min(la[i][j-1], la[i-1][j-1]));
            }
        }
    }
 

    return la[str1.length()][str2.length()];
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){

    int distance = levenshteinAlgorithm(str1, str2);
    return distance <= d;
}

bool is_adjacent(const string& word1, const string& word2){

    int adjacent = levenshteinAlgorithm(word1, word2);
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
        string last_word = ladder.back();
        for(const auto&word: word_list){
            if (is_adjacent(last_word, word)){
                if(visted.find(word) == visted.end()){
                    visted.insert(word);
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
    while (in >> word) { 
        word_list.insert(word); 
    }

    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

void my_assert(bool e) {
    cout << (e ? "Passed" : "Failed") << endl;
}