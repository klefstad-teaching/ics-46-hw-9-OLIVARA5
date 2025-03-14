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



bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    
    if (abs(len1 - len2) > d) return false;

    int edits = 0, i = 0, j = 0;
    
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            edits++;
            if (edits > d) return false;

            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }  
        } else {
            i++; j++;
        }
    }
    
    edits += abs((len1 - i) - (len2 - j));
    
    return edits <= d;
}

bool is_adjacent(const string& word1, const string& word2){

    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visted;
    if (word_list.end() == word_list.find(end_word)) {
        return {};
    }
    if (begin_word == end_word) {
        return {};
    }
    
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
    if (ladder.size() == 0) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << ' ';
        }
        cout << endl;
    }

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