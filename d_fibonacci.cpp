#include "structures.h"

tuple<vector<int>, vector<int>> dijkstra_fibonacci(int root, Graph graph){

    vector<int> distances(graph.n_vertexs, 0);
    vector<int> prevs(graph.n_vertexs, 0);

    return make_tuple(distances, prevs);
};