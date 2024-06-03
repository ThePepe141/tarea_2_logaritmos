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
#include <ctime>

using namespace std;

class Node{
    public:

    //varaibles
    int key = -1;
    tuple<int, Node> *rep; // = &(make_tuple(0, Node()));
    bool explored = false;


    //funciones
    Node();
    Node(int i);
};

class Edge{
    public:
    double weight;
    Node node1;
    Node node2;

    //constructor
    Edge(double w, int n1, int n2);
};

class Graph{
    public:

    //number of vertexs
    int n_vertexs;
    //number of edges
    int n_edges;

    //vector of vertexs
    vector<Node> vertexs;
    //vector of edges
    set<Edge> edges;

    //constructor: n_v vertexs and n_e random edges
    Graph(int n_v, int n_e);
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

    int decreaseKey(int idx, int new_value);

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

tuple<vector<int>, vector<Node>> dijkstra_fibonacci(int root, Graph graph);
tuple<vector<int>, vector<Node>> dijkstra_heap(int root, Graph graph);

