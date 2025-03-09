#include "dijkstras.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);  
    int result = RUN_ALL_TESTS();
    Graph G;
    file_to_graph("src/large.txt", G);
    
    return result;
}