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
    string filename;
    int source, destination;

    cout << "Filename: ";
    cin >> filename;
    cout << "Source: ";
    cin >> source;
    cout << "Destination: ";
    cin >> destination;

    ifstream file(filename);
    if (!file) {
        cout << "Error" << endl;
        return 1;
    }

    file_to_graph(filename, graph);
    vector<int> previous(graph.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);
    vector<int> shortest_path = extract_shortest_path(distances, previous, destination);
    int total = distances[destination];
    print_path(shortest_path, total);

    file.close();
    return 0;
}
