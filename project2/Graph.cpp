//
// Created by Lara Bastos on 26/12/2022.
//

#include <queue>
#include <set>
#include "Graph.h"

Graph::Graph(string airline){
    this->airline = airline;
    n = 0;
}

void Graph::addEdge(string src, string dest){
    Edge edge;
    edge.dest = dest;

    for (int i = 0; i < nodes.size(); i++){
        if (nodes[i].src == src) {
            nodes[i].adj.push_back(edge);
            return;
        }
    }

    list<Edge> destinations;
    destinations.push_back(edge);
    Node curr;
    curr.src = src;
    curr.adj = destinations;
    curr.visited = false;
    curr.distance = 0;
    nodes.push_back(curr);
    n++;
}
void Graph::addEdgeWithAirline(string src, string dest, string airline){
    Edge edge;
    edge.dest = dest;
    edge.airline=airline;

    for (int i = 0; i < nodes.size(); i++){
        if (nodes[i].src == src) {
            nodes[i].adj.push_back(edge);
            return;
        }
    }

    list<Edge> destinations;
    destinations.push_back(edge);
    Node curr;
    curr.src = src;
    curr.adj = destinations;
    curr.visited = false;
    curr.distance = 0;
    nodes.push_back(curr);
    n++;
}

string Graph::getAirline() {
    return airline;
}

vector<Graph::Node> Graph::getNodes() {
    return nodes;
}

void Graph::dfs_art(int v, int & i, set<string> & ans, stack<int> & s){
    nodes[v].num = nodes[v].low = i;
    i++;
    s.push(v);
    nodes[v].visited = true;

    for (Edge e : nodes[v].adj){
        string w = e.dest;
        int it;
        for (it = 0; it < nodes.size(); it++){
            if (nodes[it].src == w) break;
        }
        if (nodes[it].num == -1){
            dfs_art(it, i, ans, s);
            nodes[it].low = min(nodes[v].low, nodes[it].low);
            if (nodes[it].low >= nodes[v].num) ans.insert(nodes[v].src);
        }
        else if (nodes[it].visited){
            nodes[it].low = min(nodes[it].low, nodes[it].num);
        }
    }

    int n = s.top();
    nodes[n].visited = false;
    s.pop();
}

set<string> Graph::articulationPoints() {
    set<string> answer;
    int it = 0;
    stack<int> s;
    for (int v = 0; v < nodes.size(); v++){
        nodes[v].num = -1;
    }
    if (nodes[0].adj.size() > 1) answer.insert(nodes[0].src);

    for (int v = 1; v < nodes.size(); v++){
        if (nodes[v].num == -1){
            dfs_art(v, it, answer, s);
        }
    }

    return answer;
}




