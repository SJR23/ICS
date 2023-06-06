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
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> store;
    for(int curr = destination; curr != -1; curr = previous[curr]){
        store.push_back(curr);
    }
    reverse(store.begin(), store.end());
    int total_cost = 0;
    for(int i = 0; i < store.size() - 1; i++){
        total_cost += distances[store[i]];
    }
    return store;
}

void print_path(const vector<int>& v, int total){
    /*if(v.empty()){
        cout << "Error" << endl;
        return;
    }*/
    for(int i = 0; i<v.size(); i++){
        cout << v[i];
        if(i != v.size()-1)
            cout << " ";
    }
    cout << " " << endl;
    cout << "Total cost is " << total << endl;
}



