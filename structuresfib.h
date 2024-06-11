#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>
#include <cstdlib>
#include <ctime>

namespace GraphStructure {

    struct Edge {
        int node1;
        int node2;
        double weight;

        Edge(double w, int n1, int n2);

        bool operator<(const Edge& other) const;
    };

    struct Vertex {
        int key;

        Vertex(int k) : key(k) {}
    };

    class Graph {
    public:
        int n_vertexs;
        int n_edges;
        std::vector<Vertex> vertexs;
        std::vector<Edge> edges;

        Graph(int n_v, int n_e);
        
        void addEdge(int u, int v, double weight);
        bool isConnected();
    };

    int random_int(int i, int j);
    double random_decimal();

}

#endif
