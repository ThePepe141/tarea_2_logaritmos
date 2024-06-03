#include "structures.h"


tuple<vector<int>, vector<Node>> dijkstra_heap(Node root, Graph graph){

    //1 create distances[] and prevs[]
    vector<int> distances(graph.n_vertexs, 0);
    vector<Node> prevs(graph.n_vertexs, 0);

    //2- create Q (heap)
    minHeap heap(graph.n_vertexs);

    distances[0] = 0;
    prevs[0]  = -1;
    Pair root_pair = make_tuple(0, root);
    heap.insert(root_pair);
    root.rep = &root_pair;
    const int inf = std::numeric_limits<int>::max();
    int aux = 1;

    //4 y 5- fill heap
    for (int i=0; i<graph.n_vertexs; i++){
        if (graph.vertexs[i].key!= root.key){
            distances[i+aux] = inf;
            prevs[i+aux] = -2;
            Pair the_pair = make_tuple(inf,graph.vertexs[i]);
            graph.vertexs[i].rep = &the_pair;
            heap.insert(the_pair);
        }
        else{
            aux = 0;
        }
    }
    // search for the edge that conects the root with other vertex and change the distance
    for (const auto &edge : graph.edges) {
        if (edge.node1 == root){
            Pair p = *edge.node2.rep;
            get<0>(p) = edge.weight;
            Edge edgeToRemove = Edge(edge.weight, edge.node1 ,edge.node2);
            edge.erase(edgeToRemove);
        }
        if (edge.node2 == root){
            Pair p = *edge.node1.rep;
            get<0>(p) = edge.weight;
            Edge edgeToRemove = Edge(edge.weight, edge.node1 ,edge.node2);
            edge.erase(edgeToRemove);
        }
    }
    for (int i = 0; i< graph.n_edges; i++){
        if{
        }
    }

    //6
    return make_tuple(distances, prevs);
};