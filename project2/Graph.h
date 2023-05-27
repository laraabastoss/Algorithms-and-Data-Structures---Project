//
// Created by Lara Bastos on 26/12/2022.
//

#ifndef UNTITLED3_GRAPH_H
#define UNTITLED3_GRAPH_H
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <set>

using namespace std;

/// Simple Graph to represent all the flights
class Graph {
public:
    /// Edge that connects two nodes - associated with the flights
    struct Edge {
        /// destination of the Edge
        string dest;
        /// Airline associated with that Edge
        string airline;
    };
    /// simple Node of the represented graph
    struct Node {
        /// source airport code
        string src;
        /// bool value to determine if that Node has been visited
        bool visited;
        /// distance to the current Node, number of the order to iterate through, lowest number we can reach from that Node
        int distance, num, low;
        /// previous Node
        string prev;
        /// The list of outgoing edges (to adjacent nodes)
        list<Edge> adj;
    };

private:
        /// Graph size
        int n;
        /// Airline associated with that Graph
        string airline;
        /// Vector containing all nodes of the current Graph
        vector<Node> nodes;
public:
    /// default constructor
    Graph() = default;
    /// creates a Graph with the given airline and the other attributes as empty
    /// \param airline airline of created Graph
    Graph( string airline);
    /// Adds an edge to current graph with the given source and destination and with an empty airline
    /// \param src Edge source
    /// \param dest Edge destination
    void addEdge(string src, string dest);
    /// Adds an edge to current graph with the given source, destination and airline
    /// \param src Edge source
    /// \param dest Edge destination
    /// \param airline Edge airline
    void addEdgeWithAirline(string src, string dest, string airline);
    ///
    /// \return Graph Airline
    string getAirline();
    ///
    /// \return Graph Vector of Nodes
    vector<Node> getNodes();
    /// Depfth-first Search to find articulation points
    /// \param v starting Node
    /// \param i Node v number/order
    /// \param ans set of strings with articulation points
    /// \param s stack of visited Nodes
    void dfs_art(int v, int & i, set<string> & ans, stack<int> & s);
    /// uses the dfs_art function to find and return the articulation points
    /// \return set of strings of articulation points
    set<string> articulationPoints();

};


#endif //UNTITLED3_GRAPH_H
