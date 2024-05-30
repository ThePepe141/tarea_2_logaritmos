#include "structures.h"


tuple<vector<int>, vector<int>> dijkstra_heap(Node root, Graph graph){

    vector<int> distances(graph.n_vertexs, 0);
    vector<int> prevs(graph.n_vertexs, 0);
    for (int i=0; i<graph.n_vertexs; i++){

    }

    return make_tuple(distances, prevs);
};