#include "dijkstras.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);  
    int result = RUN_ALL_TESTS();
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> previous(G.numVertices, -1);
    int source = 0; 
    int destination = 3; 
    
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    vector<int> path = extract_shortest_path(distances, previous, destination);
    
    cout << "Shortest path from " << source << " to " << destination << ": ";
    print_path(path, path.size());
    return result;
}