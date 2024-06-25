#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <limits>
#include <set>

using namespace std;

class Node{
    public:

    //variables
    int key = -1;
    //tuple<double, Node> *rep; // = &(make_tuple(0, Node()));
    int heap_place = -1;


    //funciones
    Node();
    Node(int i);
};

struct Edge{
    int node1;
    int node2;
    double weight;
};

struct Graph{
    //vector<Edge> edges;
    int n_v;
    //set<pair<int,int>> list_edges;
    set<tuple<int, int, double>> list_edges;
};

Graph createGraph(int n_v, int n_e);

void addEdge(Graph &g, int x, int y, double w);
//par: distancia, nodo
typedef tuple<double,Node> Pair;

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

public:
    // Constructor
    minHeap(int capacity);
    // Insert a key into the min heap
    void insert(Pair k);
    // Extracts the minumum element
    Pair extractMin();
    // Recursively heapify a sub-tree
    void heapify(int i);
    //Recursively moves an element up, if needed
    void heapifyUp(int i);
    // Print the heap
    void printHeap();
    //decrease the distance value of the element in idx to new_value
    void decreaseKey(int idx, int new_value);
    //bool to know if the heap is empty
    bool empty();
    //return the pair on the idx in the heap
    Pair getPair(int idx);
};


tuple<vector<double>, vector<int>> dijkstra_heap(int root, Graph graph);

