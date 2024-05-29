#include "structures.h"

tuple<vector<int>, vector<int>> Node::dijkstra_fibonacci(Node root, vector<Node> vertexs){

    vector<int> distances(vertexs.size(), 0);
    vector<int> prevs(vertexs.size(), 0);

    return make_tuple(distances, prevs);
};