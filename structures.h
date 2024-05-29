#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Node{
    public:

    //varaibles
    int key;
    bool explored = false;

    //funciones
    Node();
    Node(int i);
    tuple<vector<int>, vector<int>> dijkstra_fibonacci(Node root, vector<Node> vertexs);
    tuple<vector<int>, vector<int>> dijkstra_heap(Node root, vector<Node> vertexs);
};

//par: distancia, nodo
typedef tuple<int,Node> Pair;


class minHeap{
private:
    // Current size of the heap
    int size;
    // Max size of heap
    int capacity;
    // Store elements as a vector
    vector<Pair> heap;
    // Returns the parent index
    int parent(int i);
    // Returns the left child
    int left(int i);
    // Returns the right child
    int right(int i);

    int decreaseKey();

public:
    // Constructor
    minHeap(int capacity);
    // Insert a key into the min heap
    void insert(Pair k);
    // Extracts the minumum element
    Pair extractMin();
    // Recursively heapify a sub-tree
    void heapify(int i);
    // Print the heap
    void printHeap();
};

class cola_fibonacci{

    int insert();
    int findMin();
    int heapify();
    int merge();
    int extractMin();
    int decreaseKey();

};

