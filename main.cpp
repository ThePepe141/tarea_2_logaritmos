#include "structures.cpp"

int main(){
    println("Ingrese el número de vértices y aristas del grafo");
    int i,j;
    println("numero de vertices 2^i");
    println("numero de aristas 2^j");
    println("i: ");
    cin >> i;
    println("j: ");
    cin >> j;
    auto inicio = chrono::high_resolution_clock::now();
    Graph g = generateGraph(i,j);
    return 0;
}