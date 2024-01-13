#ifndef EX02_ADVCPP_DIRECTEDGRAPH_H
#define EX02_ADVCPP_DIRECTEDGRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <fstream>

class DirectedGraph {
private:
    struct Edge {
        std::string v1;
        std::string v2;
        double weight;
        Edge(std::string v, std::string u, double w) : v1(std::move(v)), v2(std::move(u)), weight(w) {}

    };

    std::map<std::string, std::vector<std::shared_ptr<Edge>>> graph;

public:
    DirectedGraph();

    /*
     * Big five
     */
    DirectedGraph(const DirectedGraph &other);
    DirectedGraph &operator=(const DirectedGraph &other);
    ~DirectedGraph() = default;
    DirectedGraph(DirectedGraph &&rhs) noexcept ;
    DirectedGraph &operator=(DirectedGraph &&rhs) noexcept ;


    // Add a new vertex if none exists.
    void addVertex(const std::string& v);

    // Remove the vertex and its edges from the graph.
    void removeVertex(const std::string& v);

    /*
     * Add a new edge if none exists between two vertices,
     * Otherwise replace the existing edge with the given edge.
     * If the vertex u do not exist, add him to the graph.
     */
    void putEdge(const std::string& u, const std::string& v, double weight);

    // Remove the vertex and its edges from the graph.
    void removeEdge(const std::string& u, const std::string& v);

    // Checks if the graph contains the vertex v.
    bool containVertex(const std::string& v);

    // Checks if the edge (u,v) exists.
    bool containEdge(const std::string& u, const std::string& v);

    // Return the weight of edge (u,v), if it exists. Otherwise return 0.
    double getWeight(const std::string& u, const std::string& v);

    std::vector<std::string> get_neighbors(const std::string& vertex);

    std::vector<std::string> get_connected(const std::string& vertex);

    void print_graph(const std::string& outfile);

};


#endif //EX02_ADVCPP_DIRECTEDGRAPH_H
