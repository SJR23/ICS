#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "ladder.h"
#include "dijkstras.h"
using namespace std;

int main() {
    Graph graph;
    file_to_graph("small.txt", graph);
    int numVertices = graph.numVertices;

    for(int destination = 0; destination < numVertices; destination++){
        vector<int> previous(numVertices, -1);
        vector<int> distances = dijkstra_shortest_path(graph, destination, previous);
        vector<int> shortestPath = extract_shortest_path(distances, previous, destination);
        cout << "Get to: " << destination << endl;
        cout << "Total cost: " << distances[destination] << endl;
        cout << "Path: ";
        print_path(shortestPath, distances[destination]);
        cout << endl;
    }
    return 0;
}
