#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(DijkstraTest, GivenGraph) {
    Graph G;
    file_to_graph("src/large.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0); 
    EXPECT_EQ(distances[1], 7);
    EXPECT_EQ(distances[2], 15);
    EXPECT_EQ(distances[3], 5);
    EXPECT_EQ(distances[4], 14);
    EXPECT_EQ(distances[5], 11);
    EXPECT_EQ(distances[6], 12);
}

TEST(DijkstraTest, ExtractShortestPath) {
    Graph G;
    file_to_graph("src/large.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    vector<int> path = extract_shortest_path(distances, previous, 6);
    
    vector<int> expected_path = {0, 3, 5, 6};
    EXPECT_EQ(path, expected_path);
}

TEST(DijkstraTest, Graph3) {
    Graph G;
    file_to_graph("src/small.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);  
    EXPECT_EQ(distances[1], 3);  
    EXPECT_EQ(distances[2], 6); 
    EXPECT_EQ(distances[3], 1); 
}

TEST(DijkstraTest, PathSource1To3) {
   Graph G;
    file_to_graph("src/small.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 1, previous);
    vector<int> path = extract_shortest_path(distances, previous, 3);

    vector<int> expected_path = {1, 0, 3};
    EXPECT_EQ(path, expected_path);
}


TEST(EditDistanceWithinTest, SameWord) {
    EXPECT_TRUE(edit_distance_within("dog", "dog", 1));  
}

TEST(EditDistanceWithinTest, OneCharacterDifference) {
    EXPECT_TRUE(edit_distance_within("fog", "dog", 1));  
}

TEST(EditDistanceWithinTest, MultipleEdits) {
    EXPECT_FALSE(edit_distance_within("hello", "holla", 1)); 
}

TEST(EditDistanceWithinTest, LengthDifference) {
    EXPECT_FALSE(edit_distance_within("hello", "hellooo", 1)); 
}

TEST(EditDistanceWithinTest, LengthDifferenceWithinLimit) {
    EXPECT_TRUE(edit_distance_within("hello", "helloo", 2)); 
}


TEST(IsAdjacentTest, AdjacentWords) {
    EXPECT_TRUE(is_adjacent("hello", "hella")); 
}

TEST(IsAdjacentTest, NonAdjacentWords) {
    EXPECT_FALSE(is_adjacent("hello", "holla"));  
}

TEST(IsAdjacentTest, LengthDifference) {
    EXPECT_FALSE(is_adjacent("dog", "doggg")); 
}


TEST(GenerateWordLadderTest, BasicLadder) {
    std::set<std::string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
    std::vector<std::string> ladder = generate_word_ladder("hit", "cog", word_list);
    std::vector<std::string> expected_ladder = {"hit", "hot", "dot", "dog", "cog"};
    EXPECT_EQ(ladder, expected_ladder);
}

TEST(GenerateWordLadderTest, NoLadderPossible) {
    std::set<std::string> word_list = {"hot", "dot", "dog", "lot", "log"};
    std::vector<std::string> ladder = generate_word_ladder("hit", "cog", word_list);
    EXPECT_TRUE(ladder.empty()); 
}

TEST(GenerateWordLadderTest, SameWordStartEnd) {
    std::set<std::string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
    std::vector<std::string> ladder = generate_word_ladder("hit", "hit", word_list);
    std::vector<std::string> expected_ladder = {};
    EXPECT_EQ(ladder, expected_ladder);  
}

TEST(GenerateWordLadderTest, SingleStepLadder) {
    std::set<std::string> word_list = {"hot", "dot", "dog"};
    std::vector<std::string> ladder = generate_word_ladder("hit", "hot", word_list);
    std::vector<std::string> expected_ladder = {"hit", "hot"};
    EXPECT_EQ(ladder, expected_ladder); 
}

TEST(GenerateWordLadderTest, LargerLadder) {
    std::set<std::string> word_list = {"hit", "hot", "dot", "dog", "lot", "log", "cog"};
    std::vector<std::string> ladder = generate_word_ladder("hit", "cog", word_list);
    std::vector<std::string> expected_ladder = {"hit", "hot", "dot", "dog", "cog"};
    EXPECT_EQ(ladder, expected_ladder); 
}

TEST(GenerateWordLadderTest, NoWordsInBetween) {
    std::set<std::string> word_list = {"cat", "bat", "rat", "sat"};
    std::vector<std::string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_TRUE(ladder.empty());  
}
