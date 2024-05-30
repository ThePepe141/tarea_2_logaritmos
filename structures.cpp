#include "structures.h"

//-----------------Node----------------------------------
Node::Node(){
    key = 0;
}
Node::Node(int i){
    key = i;
}
//------------------------------------------------------
//------------------edge---------------------------------
Edge::Edge(double w, int n1, int n2){
    weight = w;
    node1 = n1;
    node2 = n2;
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
        uniform_int_distribution<> dis(i, j);
        return dis(gen);
    }
}

/*Generates a random number between (0,1]*/
double random_decimal(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(std::nextafter(0.0, 1.0), 1.0);
    return dis(gen);
}

/*Creates a graph with n_v vertexs and n_e edges*/
Graph::Graph(int n_v, int n_e){
    n_vertexs = n_v;
    n_edges = n_e;
    vertexs.resize(n_vertexs);
    edges.resize(n_edges);
    vertexs[0] = 0;
    //Fill "vertexs" and adds v-1 edges to "edges"
    for (int i=1; i<n_vertexs; i++){
        vertexs[i] = i;
        edges[i-1] = Edge(random_decimal(), i, random_int(i-1, i));

    }
    //fill the rest of "edges"
    int border = n_edges-(n_vertexs-1);
    for (int j=0; j<border; j++){
        int random1 = random_int(0, n_vertexs-1);
        int random2 = random_int(0, n_vertexs-1);
        edges[border+j] = Edge(random_decimal(), random1, random2);
    }
    
}
//--------------------------------------------------------
//-----------------Heap-------------------------------------
int minHeap::decreaseKey(int idx, int new_value){
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
        //Node node(-1);
        //Pair p(-1,node);
        //return p;
        Pair p(-1, -1);
        return p;
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


//----------------------------------------------------------------
//---------------cola Fibonacci-----------------------------------