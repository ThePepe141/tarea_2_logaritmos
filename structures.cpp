#include "structures.h"

//-----------------Node----------------------------------
Node::Node(){
    key = 0;
}
Node::Node(int i){
    key = i;
}
//------------------------------------------------------
//------------------Graph---------------------------------
/* Generates a random number between [i, j]*/
int random_int(int i, int j){
    if (i==j){
        return i;
    }
    else{
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(i, j);
        return distr(gen);
    }
}

/*Generates a random number between (0,1]*/
double random_decimal(){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_real_distribution<double> distr(0, 1); // define the range
    return distr(gen);
}
void addEdge(Graph &g, int x, int y, double w){
    int size = g.list_edges.size();
    if (x > y){
        swap(x, y);
    }
    g.list_edges.insert(make_pair(x, y));
    
    if (g.list_edges.size() == size){
        return;
    }
    g.edges.push_back({x,y,w});
    g.edges.push_back({y,x,w});
}
/*Creates a graph with n_v vertexs and n_e edges*/
Graph createGraph(int i, int j){
    int n_vertexs = 1 << i;
    int n_edges = 1 << j;

    Graph g;
    //Fill "vertexs" and adds v-1 edges to "edges"
    for (int i=1; i<n_vertexs; i++){
        int u = random_int(0, i-1);
        double weight = random_decimal();
        addEdge(g, u, i, weight);
    }
    //fill the rest of "edges"
    while(g.list_edges.size() < n_edges){
        int u = random_int(0, n_vertexs-1);
        int v = random_int(0, n_vertexs-1);
        double weight = random_decimal();
        while(u == v){
            v = random_int(0, n_vertexs-1);
        }
        addEdge(g, u, v, weight);
    }
    return g;
}
//--------------------------------------------------------
//-----------------Heap-------------------------------------
void minHeap::decreaseKey(int idx, int new_value){
    get<0>(heap[idx]) = new_value;
    heapify(idx);
}

minHeap::minHeap(int capacity){
    size = 0;
    this->capacity = capacity;
    heap.resize(capacity);
}

int minHeap::parent(int i){
    return (i - 1) / 2;
}

int minHeap::left(int i){
    return 2 * i + 1;
}

int minHeap::right(int i){
    return 2 * i + 2;
}

// Insert key into the minHeap
void minHeap::insert(Pair k){
    // Make sure there is still space in the heap
    if(size == capacity){
        cout << "MIN HEAP FULL!" << endl;
        return;
    }

    // Increse the amount of elements in the heap
    size++;

    // Insert the new key at the end
    int i = size - 1;
    heap[i] = k;

    // Fix the min heap property
    // Moves the element up until i >= parent or root
    std::get<0>(heap[i]);
    while(i != 0 && std::get<0>(heap[parent(i)]) > std::get<0>(heap[i])){
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

// Recursive function to maintain structure
void minHeap::heapify(int i){
    // Set initial conditions (index)
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // Find the smallest element of the three
    if((l < size) && (std::get<0>(heap[l]) < std::get<0>(heap[smallest]))){
        smallest = l;
    }if((r < size) && (std::get<0>(heap[r]) < std::get<0>(heap[smallest]))){
        smallest = r;
    }

    // If the smallest of l or r, continue heapify
    if(smallest != i){
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

// Removes the smallest element and fixes the order
Pair minHeap::extractMin(){
    // Check if the heap is empty
    if(size == 0){
        cout << "EMPTY HEAP" << endl;
        Node node(-1);
        Pair p(-1,node);
        return p;
        //Pair p(-1, -1);
        //return p;
    // Check if there is only 1 element
    }else if(size == 1){
        size--;
        return heap[0];
    // Normal extraction
    }else{
        // Store the root
        Pair root = heap[0];

        // Maintain heap shape and then order
        heap[0] = heap[size - 1];
        size--;
        heapify(0);

        // Return min element
        return root;
    }
}
void printGraph(Graph &g){
    for(Edge e: g.edges){
        cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
    }
}


//----------------------------------------------------------------
//---------------cola Fibonacci-----------------------------------