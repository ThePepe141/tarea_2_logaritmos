#include "structures.h"
#include <queue>

namespace GraphStructure {

    Edge::Edge(double w, int n1, int n2) : node1(n1), node2(n2), weight(w) {}

    bool Edge::operator<(const Edge& other) const {
        return this->weight < other.weight;
    }

    int random_int(int i, int j) {
        return rand() % (j - i + 1) + i;
    }

    double random_decimal() {
        return static_cast<double>(rand()) / RAND_MAX;
    }

    Graph::Graph(int n_v, int n_e) : n_vertexs(n_v), n_edges(n_e) {
        srand(static_cast<unsigned>(time(0)));

        for (int i = 0; i < n_vertexs; ++i) {
            vertexs.push_back({i});
        }

        for (int i = 1; i < n_vertexs; ++i) {
            int j = random_int(0, i - 1);
            double weight = random_decimal();
            edges.push_back({weight, vertexs[i].key, vertexs[j].key});
        }

        for (int i = 0; i < n_edges - (n_vertexs - 1); ++i) {
            int u = random_int(0, n_vertexs - 1);
            int v = random_int(0, n_vertexs - 1);
            while (v == u) {
                v = random_int(0, n_vertexs - 1);
            }
            double weight = random_decimal();
            edges.push_back({weight, vertexs[u].key, vertexs[v].key});
        }
    }

    void Graph::addEdge(int u, int v, double weight) {
        edges.push_back({weight, u, v});
    }

    bool Graph::isConnected() {
        std::vector<bool> visited(n_vertexs, false);
        std::queue<int> q;
        int count = 0;

        q.push(0);
        visited[0] = true;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;
            for (const Edge &edge : edges) {
                int neighbor = -1;
                if (edge.node1 == node) {
                    neighbor = edge.node2;
                } else if (edge.node2 == node) {
                    neighbor = edge.node1;
                }
                if (neighbor != -1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return count == n_vertexs;
    }
}
