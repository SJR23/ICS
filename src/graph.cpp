#include "graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <numeric>

using namespace std;

DisjointSet::DisjointSet(int numVertices){
    for(int i = 0; i < numVertices; i++)
        subsets.push_back({i});
}

void DisjointSet::makeSet(Vertex x){
    subsets[x].parent = x;
}

Vertex DisjointSet::findSet(Vertex x){
    if(x != subsets[x].parent)
        subsets[x].parent = findSet(subsets[x].parent);
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y){
    if(!(findSet(x) == findSet(y)))
        subsets[findSet(y)].parent = findSet(x);
}

Graph Graph::sort_edges() const{
    Graph get = *this;
    sort(get.begin(), get.end(),[](const Edge& a, const Edge& b){
        return a.weight < b.weight;
    });
    return get;
}

VertexList Graph::edges_from(Vertex vertex)const{
    VertexList send;
    for(const Edge& ed : *this){
        if(ed.u == vertex)
            send.push_back(ed.v);
        if(ed.v == vertex)
            send.push_back(ed.u);
    }
    return send;
}

void error(string msg){
    cerr << "Error: " << msg << endl;
}

void file_to_graph(string filename, Graph& G){
    ifstream f(filename);
    if(!f)
        error("Invalid file name: unable to open");
    /*while(true){
        Edge ed;
        if(f >> ed)
            G.push_back(ed);
        else
            break;
    }*/
    f >> G;
    f.close();
}

int sum_weights(const EdgeList& L){
    int add = 0;
    for(const Edge& ed : L)
        add += ed.weight;
    return add;
}

EdgeList Kruskals(const Graph& G){
    DisjointSet ds{G.numVertices};
    const Graph sorted_edges = G.sort_edges();
    size_t solution_size = G.numVertices-1;
    EdgeList result;
    
    for(const Edge& e : sorted_edges){
        Vertex uRoot = ds.findSet(e.u);
        Vertex vRoot = ds.findSet(e.v);
        if(uRoot != vRoot){
            ds.unionSets(uRoot, vRoot);
            result.push_back(e);
            if(result.size() >= solution_size) break;
        }
    }
    return result;
}

VertexList dfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> visited(graph.size(), false);
    stack<Vertex> stk;
    visited[startVertex] = true;
    stk.push(startVertex);
    while(!stk.empty()){
        Vertex vertex = stk.top();
        stk.pop();
        result.push_back(vertex);
        for(Vertex v : graph.edges_from(vertex)){
            if(!visited[v]){
                visited[v] = true;
                stk.push(v);
            }
        }
    }
    return result;
}

VertexList bfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> queue;
    visited[startVertex] = true;
    queue.push(startVertex);
    while(!queue.empty()){
        Vertex vertex = queue.front();
        queue.pop();
        result.push_back(vertex);
        for(Vertex v : graph.edges_from(vertex)){
            if(!visited[v]){
                visited[v] = true;
                queue.push(v);
            }
        }
    }
    return result;
}

string get_arg(int argc, char* argv[], string def){
    if(argc > 1){
        return argv[1];
    }
    return def;
}