#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <fstream>
#include <numeric>
#include "FibonacciHeap.h"
#include "structures.h"

using namespace std;
using namespace FibonacciHeapStructure;
using namespace GraphStructure;

void dijkstraFibonacci(Graph &graph, int src) {
    int V = graph.n_vertexs;
    vector<double> dist(V, numeric_limits<double>::infinity());
    vector<int> prev(V, -1);

    FibonacciHeap heap;
    vector<FibonacciNode*> nodes(V, nullptr);

    dist[src] = 0;
    nodes[src] = new FibonacciNode(0);
    heap.INSERT(nodes[src]);

    for (int v = 0; v < V; ++v) {
        if (v != src) {
            nodes[v] = new FibonacciNode(numeric_limits<int>::max());
            heap.INSERT(nodes[v]);
        }
    }

    while (heap.MINIMUM() != nullptr) {
        FibonacciNode* minNode = heap.EXTRACT_MIN();
        int u = -1;

        for (int i = 0; i < V; ++i) {
            if (nodes[i] == minNode) {
                u = i;
                break;
            }
        }

        if (u == -1) continue;

        for (const Edge &edge : graph.edges) {
            if (edge.node1 == u) {
                int v = edge.node2;
                double weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    heap.DECREASE_KEY(nodes[v], dist[v]);
                }
            } else if (edge.node2 == u) {
                int v = edge.node1;
                double weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    heap.DECREASE_KEY(nodes[v], dist[v]);
                }
            }
        }
    }
}

int main() {
    vector<int> v_values = {1 << 10, 1 << 12, 1 << 14};
    vector<int> e_values = {1 << 16, 1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 21, 1 << 22};
    int grafnumber;
    cout<<"Ingrese el número de grafos: \n";
    cin >> grafnumber;
    ofstream results("execution_times.csv");
    results << "v,e,time\n";

    for (int v : v_values) {
        for (int e : e_values) {
            vector<double> execution_times;
            if(e > v*(v-1)/2){
                break;
            } // No se pueden tener más aristas que v*(v-1)/2 (grafo completo)
            for (int i = 0; i < grafnumber; ++i) {
                Graph graph(v, e);
                if (!graph.isConnected()) {
                    std::cerr << "El grafo generado no es conexo." << std::endl;
                    continue;
                }

                auto start = chrono::high_resolution_clock::now();
                dijkstraFibonacci(graph, 0);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                execution_times.push_back(duration.count());
            }

            double avg_time = accumulate(execution_times.begin(), execution_times.end(), 0.0) / execution_times.size();
            results << v << "," << e << "," << avg_time << "\n";
            cout << "Average execution time for v = " << v << " and e = " << e << " is " << avg_time << " seconds." << endl;
        }
    }

    results.close();
    return 0;
}
