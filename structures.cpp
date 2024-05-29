#include "structures.h"


//-----------------Heap-------------------------------------
Node::Node(){
    key = 0;
};
Node::Node(int i){
    key = i;
};
void Heap::insert(Pair par){
    heap.push_back(par);
    heapifyUp(heap.size() -1);
};

bool Heap::isEmpty(){
    return heap.size() == 0;
};

Pair Heap::extactMin(){
    try{
        if (heap.size() != 0) {
            Pair min = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if(!heap.empty()){
                heapifyDown(0);
            }
            return min;
        } else {
            throw(1);
        }
    }
    catch(int){
        cout << "Heap is empty";
    }
};

int Heap::parent(int i){
    return floor((i-1)/2);
};

int Heap::left_child(int i){
    return 2*i + 1;
};

int Heap::right_child(int i){
    return 2*i + 2;
};


//----------------------------------------------------------------
//---------------cola Fibonacci-----------------------------------