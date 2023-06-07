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
    vector<bool> visited(n, false);
    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(const pair<int, int>&, const pair<int, int>&)>> pq([](const pair<int, int>& a, const pair<int, int>& b){
        return a.first > b.first;
    });
    pq.push({0, source});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;

        for(const Edge& edge : graph[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    int curr = destination;
    if(previous[curr] == -1) return path;
    for(int i = 0; curr != -1; i++, curr = previous[curr]){
        path.push_back(curr);
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
