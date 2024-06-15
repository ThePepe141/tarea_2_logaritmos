#include "structures.h"


tuple<vector<int>, vector<Node>> dijkstra_heap(int root, Graph graph){

    //1 create distances[] and prevs[]
    vector<int> distances(graph.n_v, 0);
    vector<Node> prevs(graph.n_v, 0);

    //vector with nodes, the idea is for the idx of the node to match his key value
    vector<Node> nodes;

    //2- create Q (heap)
    minHeap heap(graph.n_v);

    //3- add pair (0,root) to Q
    distances[0] = 0;
    prevs[0]  = -1;
    Node root_node = Node(root);
    Pair root_pair = make_tuple(0, root_node);
    heap.insert(root_pair);
    root_node.rep = &root_pair;
    const int inf = std::numeric_limits<int>::max();
    int aux = 1;

    //4 y 5- fill heap
    for (int i=0; i<graph.n_v; i++){
        if (i != root){
            distances[i+aux] = inf;
            prevs[i+aux] = -2;
            Node node_i = Node(i);
            Pair the_pair = make_tuple(inf,node_i);
            node_i.rep = &the_pair;
            nodes.push_back(node_i);
            heap.insert(the_pair);
        }
        else{
            aux = 0;
            nodes.push_back(root_node);
        }
    }
    //caso particular: root_pair
    // search for the edge that conects the root with other vertex and change the distance
    for (const auto &edge : graph.edges) {
        if (edge.node1 == root){
            //search in nodes the node connected with root, then take his rep value
            Pair p = *nodes[edge.node2].rep;
            heap.decreaseKey(get<1>(p).heap_place, edge.weight);
            Edge edgeToRemove = Edge(edge.weight, edge.node1 ,edge.node2);
            edge.erase(edgeToRemove);
        }
        if (edge.node2 == root){
            Pair p = *nodes[edge.node1].rep;
            heap.decreaseKey(get<1>(p).heap_place, edge.weight);
            Edge edgeToRemove = Edge(edge.weight, edge.node1 ,edge.node2);
            edge.erase(edgeToRemove);
        }
    }
    
    //caso iterativo
    while(!heap.empty()){
        Pair the_shortest = heap.extractMin();

    }

    //6
    return make_tuple(distances, prevs);
};