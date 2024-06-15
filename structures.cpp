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
    g.n_v = n_vertexs;
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
int minHeap::parent(int i){
    return (i - 1) / 2;
}

int minHeap::left(int i){
    return 2 * i + 1;
}

int minHeap::right(int i){
    return 2 * i + 2;
}

minHeap::minHeap(int capacity){
    size = 0;
    this->capacity = capacity;
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
    int place = size - 1;
    get<1>(k).heap_place = place;
    heap.push_back(k);

    // Fix the min heap property
    // Moves the element up until i >= parent or root
    while(place != 0 && std::get<0>(heap[parent(place)]) > std::get<0>(heap[place])){
        //change the heap_place values of the nodes
        int to_mod = get<1>(heap[parent(place)]).heap_place;
        get<1>(heap[place]).heap_place = to_mod;
        get<1>(heap[parent(place)]).heap_place = place;
        //swap the pairs
        swap(heap[place], heap[parent(place)]);
        place = parent(place);
    }
}

// Removes the smallest element and fixes the order
Pair minHeap::extractMin(){
    // Check if the heap is empty
    if(size == 0){
        throw std::runtime_error("The minHeap is empty");
    // Check if there is only 1 element
    }else if(size == 1){
        size--;
        get<1>(heap[0]).heap_place = -1;
        Pair root = heap[0];
        heap.pop_back();
        return root;
    // Normal extraction
    }else{
        // Store the root
        get<1>(heap[0]).heap_place = -1;
        Pair root = heap[0];

        // Maintain heap shape and then order
        //heap[0] = heap[size - 1];
        get<1>(heap[size-1]).heap_place = 0;
        swap(heap[0], heap[size-1]);
        heap.pop_back();
        size--;
        heapify(0);

        // Return min element
        return root;
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
        //change the heap_place values of the nodes
        int to_mod = get<1>(heap[smallest]).heap_place;
        get<1>(heap[i]).heap_place = to_mod;
        get<1>(heap[smallest]).heap_place = i;
        //swap the nodes
        swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

void minHeap::heapifyUp(int i){
    if (i!=0){
        int dad = parent(i);
        if (dad >=0 && get<0>(heap[dad]) > get<0>(heap[i])){
            //change the heap_place values of the nodes
            int to_mod = get<1>(heap[parent(dad)]).heap_place;
            get<1>(heap[i]).heap_place = to_mod;
            get<1>(heap[dad]).heap_place = i;
            //swap the nodes
            swap(heap[dad], heap[i]);
            heapifyUp(dad);
        }
    }
}

void minHeap::decreaseKey(int idx, int new_value){
    if (get<0>(heap[idx]) > new_value){
        get<0>(heap[idx]) = new_value;
        heapifyUp(idx);
    }
}

bool minHeap::empty(){
    return size==0;
}

//----------------------------------------------------
void printGraph(Graph &g){
    for(Edge e: g.edges){
        cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
    }
}


//----------------------------------------------------------------
//---------------cola Fibonacci-----------------------------------