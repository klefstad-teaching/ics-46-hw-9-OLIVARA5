#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <cmath>
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    vector<bool> discovered(numVertices, false); 
    vector<int> distances(numVertices, INF);
    distances[source] = 0;
    previous.resize(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    while(!pq.empty()){
        int current = pq.top().second;
        pq.pop();
        if(discovered[current]){
            continue;
        }
        discovered[current] = true;
        for(const Edge& edge: G[current]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!discovered[v] && distances[current] + weight < distances[v]){
                distances[v] = distances[current] + weight;
                previous[v] = current;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for(int current = destination; current != -1; current = previous[current]){
        path.insert(path.begin(), current);
    }
    return path;
}

void print_path(const vector<int>& v, int total){
    if(!v.empty()){
        for(size_t current = 0; current < v.size(); ++current){
        cout << v[current] << " ";
    }
    }
    cout << "\n" << "Total cost is " << total << endl;
}