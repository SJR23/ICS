#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"

using namespace std;


vector<int> dijkstra_shortest_path(const Graph& graph, int source, vector<int>& previous) {
    int n = graph.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for(const Edge& edge : graph[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(make_pair(distance[v], v));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    
    if(distances[destination] == INF) return path;
    int curr = destination;
    while(curr != -1){
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    for(int i = 0; i<v.size(); i++){
        cout << v[i];
        if(i != v.size()-1)
            cout << " ";
    }
    if(!(v.empty()))
        cout << " ";
    cout << endl << "Total cost is " << total << endl;
}
