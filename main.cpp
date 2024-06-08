#include "structures.cpp"
using namespace std;

int main(){
    cout<<"Ingrese el número de vértices y aristas del grafo \n";
    int i,j;
    cout<<"numero de vertices 2^i \n";
    cout<<"numero de aristas 2^j \n";
    cout<<"i: \n";
    cin >> i;
    cout<<"j: \n";
    cin >> j;
    
    Graph g = createGraph(i,j);
    printGraph(g);
    return 0;
}