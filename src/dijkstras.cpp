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

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> store;
    int curr = destination;
    while(curr >= 0){
        store.push_back(curr);
        curr = previous[curr];
    }
    reverse(store.begin(), store.end());
    return store;
}

void print_path(const vector<int>& v, int total){
    if(v.empty()){
        cout << "Error" << endl;
        return;
    }
    for(int i = 0; i<v.size(); i++){
        cout << v[i];
        if(i != v.size()-1)
            cout << " ";
    }
    cout << " " << endl;
    cout << "Total cost is " << total << endl;
}



