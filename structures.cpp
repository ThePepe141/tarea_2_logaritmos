#include "structures.h"


//-----------------Heap-------------------------------------
Node::Node(){
    key = 0;
};
Node::Node(int i){
    key = i;
};
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
    std::get<0>(heap[i])
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
    // Check if there is only 1 element
    }else if(size == 1){
        size--;
        return heap[0];
    // Normal extraction
    }else{
        // Store the root
        int root = heap[0];

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