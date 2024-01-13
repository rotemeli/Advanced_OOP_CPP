#include "DirectedGraph.h"


DirectedGraph::DirectedGraph() {
    graph = std::map<std::string, std::vector<std::shared_ptr<Edge>>>();
}

DirectedGraph::DirectedGraph(const DirectedGraph &other) {
    graph = std::map<std::string, std::vector<std::shared_ptr<Edge>>>(other.graph);
}

DirectedGraph &DirectedGraph::operator=(const DirectedGraph &other) {
    if(this == &other) {
        return *this;
    }
    graph.clear();
    graph = std::map<std::string, std::vector<std::shared_ptr<Edge>>>(other.graph);
    return *this;
}

DirectedGraph::DirectedGraph(DirectedGraph &&rhs) noexcept {
    graph = rhs.graph;
}

DirectedGraph &DirectedGraph::operator=(DirectedGraph &&rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }
    graph.operator=(std::move(rhs.graph));
    return *this;
}

void DirectedGraph::addVertex(const std::string& v) {
    if(!containVertex(v)) {
        for(auto & it : graph) {
            if(it.first != v) {
            }
        }
        graph.insert({v, std::vector<std::shared_ptr<Edge>>()});
    }
}

void DirectedGraph::removeVertex(const std::string& v) {
    if(containVertex(v)) {
        for(auto & it : graph) {
            if(it.first != v) {
                for(auto it2 = it.second.begin(); it2 != it.second.end(); it2++) {
                    if((*it2)->v2 == v) {
                        it.second.erase(it2);
                        break;
                    }
                }
            }
        }
        graph.erase(v);
    }
}

void DirectedGraph::putEdge(const std::string& u, const std::string& v, double weight) {
    if(!containVertex(u)) {
        addVertex(u);
    }
    if(containEdge(u, v)) {
        for(const std::shared_ptr<Edge>& edge : graph[u]) {
            if(edge->v2 == v) {
                edge->weight = weight;
            }
        }
    }
    else {
        std::shared_ptr<Edge> new_edge(new Edge(u, v, weight));
        graph[u].push_back(new_edge);
    }
}

void DirectedGraph::removeEdge(const std::string &u, const std::string &v) {
    if(!containEdge(u, v)) {
        return;
    }
    for(auto it = graph[u].begin(); it != graph[u].end(); it++) {
        if((*it)->v2 == v) {
            graph[u].erase(it);
            break;
        }
    }
}

bool DirectedGraph::containVertex(const std::string& v) {
    if(graph.find(v) == graph.end()) {
        return false;
    }
    return true;
}

bool DirectedGraph::containEdge(const std::string &u, const std::string &v) {
    if(containVertex(u)) {
        for(auto & it : graph[u]) {
            if((*it).v2 == v) {
                return true;
            }
        }
    }
    return false;
}

double DirectedGraph::getWeight(const std::string& u, const std::string& v) {
    if(containEdge(u, v)) {
        for(auto & it : graph[u]) {
            if(it->v2 == v) {
                return it->weight;
            }
        }
    }
    return 0;
}

std::vector<std::string> DirectedGraph::get_neighbors(const std::string &vertex) {
    std::vector<std::string> res;
    if(!containVertex(vertex)) {
        return res;
    }
    for(const std::shared_ptr<Edge>& e : graph[vertex]) {
        res.push_back(e->v2);
    }
    return res;
}

std::vector<std::string> DirectedGraph::get_connected(const std::string &vertex) {
    std::vector<std::string> res;
    for(auto & it : graph) {
        if(it.first != vertex) {
            for(auto it2 = it.second.begin(); it2 != it.second.end(); it2++) {
                if((*it2)->v2 == vertex) {
                    res.push_back(it.first);
                }
            }
        }
    }
    return res;
}

void DirectedGraph::print_graph(const std::string &outfile) {
    std::ofstream file(outfile, std::ios::out | std::ios::app);
    if(file.is_open()) {
        for(auto & it : graph) {
            file << it.first << " : ";
            for(const std::shared_ptr<Edge>& e : it.second) {
                file << e->v2 << "(" << e->weight << ") " << " ";
            }
            file << std::endl;
        }
    }
    file.close();
}
