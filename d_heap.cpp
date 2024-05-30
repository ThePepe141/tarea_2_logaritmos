#include "structures.h"


tuple<vector<int>, vector<int>> dijkstra_heap(int root, Graph graph){

    //1 create distances[] and prevs[]
    vector<int> distances(graph.n_vertexs, 0);
    vector<int> prevs(graph.n_vertexs, 0);

    //create Q (heap)
    minHeap heap(graph.n_vertexs);
 
    distances[0] = 0;
    prevs[0]  = -1;
    heap.insert(make_tuple(0, -1));

    const int inf = std::numeric_limits<int>::max();
    int aux = 1;

    //fill heap
    for (int i=0; i<graph.n_vertexs; i++){
        if (graph.vertexs[i]!= root){
            distances[i+aux] = inf;
            prevs[i+aux] = -2;
            heap.insert(make_tuple(inf,graph.vertexs[i]));
        }
        else{
            aux = 0;
        }
    }

    return make_tuple(distances, prevs);
};