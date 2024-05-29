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


class Heap{
    public:
    void insert(Pair par);
    Pair extactMin();
    bool isEmpty();

    private:
    std::vector<Pair> heap;
    void heapifyDown(int i);
    void heapifyUp(int i);
    int parent(int i);
    int left_child(int i);
    int right_child(int i);
    int decreaseKey();

};

class cola_fibonacci{

    int insert();
    int findMin();
    int heapify();
    int merge();
    int extractMin();
    int decreaseKey();

};

