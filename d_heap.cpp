#include "structures.cpp"

tuple<vector<double>, vector<int>> dijkstra_heap(int root, Graph graph){

    const double inf = std::numeric_limits<int>::max();
    
   
    //1 create distances[] and prevs[]
    vector<double> distances(graph.n_v, inf);
    vector<int> prevs(graph.n_v, -2);

    //vector with nodes, the idea is for the idx of the node to match his key value
    vector<Node> nodes;

   

    //2- create Q (heap)
    minHeap heap(graph.n_v);

 

    //3- add pair (0,root) to Q
    Node root_node = Node(root);
    Pair root_pair = make_tuple(0, root_node);
    heap.insert(root_pair);
    //root_node.rep = &root_pair;

   

    //4 y 5- fill heap
    for (int i=0; i<graph.n_v; i++){
        if (i != root){
            Node node_i = Node(i);
            Pair the_pair = make_tuple(inf,node_i);
            //node_i.rep = &the_pair;
            nodes.push_back(node_i);
            heap.insert(the_pair);
        }
        else{
            distances[i] = 0.0;
            prevs[i] = -1;
            nodes.push_back(root_node);
        }
    }


    
    while(!heap.empty()){
        //cout << "comienza el while" << endl;
        Pair the_shortest = heap.extractMin();
        //tuple<int,   int,   double> edge
        //       0      1      2
        //       nodo1 nodo2   peso
        //cout << "pasa el extactmin" << endl;
        for (const auto &edge : graph.list_edges) {
            //cout << "comienzo el for: "  << get<0>(edge) << ", " << get<1>(edge) << ", " << get<2>(edge) <<  endl;
            //si el nodo1 del edge es igual al nodo en the_shortest
            if (get<0>(edge) == get<1>(the_shortest).key){
                //cout << "caso1 funciona" << endl;
                //Pair p = *nodes[get<1>(edge)].rep;
                Pair p = heap.getPair(nodes[get<1>(edge)].heap_place);
                //cout << "caso1 crea p" << endl;
                if (distances[get<1>(edge)]> distances[get<0>(edge)] + get<2>(edge)){
                    heap.decreaseKey(get<1>(p).heap_place, get<2>(edge));
                    //cout << "caso1 decreaseKey exitoso" << endl;
                    distances[get<1>(edge)] = distances[get<0>(edge)] + get<2>(edge);
                    prevs[get<1>(edge)] = nodes[get<0>(edge)].key;
                }
                //cout << "caso 1 pasaa el if" << endl;
                //graph.list_edges.erase(edge);
                //cout << "caso 1 pasa el erase" << endl;
            }
            //si el nodo2 del edge es igual al nodo en the_shortest
            else if (get<1>(edge) == get<1>(the_shortest).key){
                //cout << "caso 2 funciona" << endl;
                //Pair p = *nodes[get<0>(edge)].rep;
                Pair p = heap.getPair(nodes[get<0>(edge)].heap_place);
                if (distances[get<0>(edge)] > distances[get<1>(edge)] + get<2>(edge)){
                    heap.decreaseKey(get<1>(p).heap_place, get<2>(edge));
                    distances[get<0>(edge)] = distances[get<1>(edge) + get<2>(edge)];
                    prevs[get<0>(edge)] = nodes[get<1>(edge)].key;
                }
                //graph.list_edges.erase(edge);
            }
    }

    }

    //6
    return make_tuple(distances, prevs);
};