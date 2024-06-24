#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <fstream>
#include <numeric>
#include "d_heap.cpp"
using namespace std;

int main() {
    vector<int> v_values = {10, 12, 14};
    vector<int> e_values = {16, 17, 18, 19, 20,  21, 22};
    int grafnumber;
    cout<<"Ingrese el número de grafos: \n";
    cin >> grafnumber;
    ofstream results("execution_times.csv");
    results << "v,e,time\n";

    for (int v : v_values) {
        for (int e : e_values) {
            vector<double> execution_times;
            if(e > v*(v-1)/2){
                break;
            } // No se pueden tener más aristas que v*(v-1)/2 (grafo completo)
            for (int i = 0; i < grafnumber; ++i) {
                Graph g = createGraph(v,e);

                auto start = chrono::high_resolution_clock::now();
                cout << "probemos dijkstra" << endl;
                dijkstra_heap(0, g);
                cout << "dijkstra funciona" << endl;
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                execution_times.push_back(duration.count());
            }

            double avg_time = accumulate(execution_times.begin(), execution_times.end(), 0.0) / execution_times.size();
            results << v << "," << e << "," << avg_time << "\n";
            cout << "Average execution time for v = " << v << " and e = " << e << " is " << avg_time << " seconds." << endl;
        }
    }

    results.close();
    return 0;
}

/*
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
    cout << "grafo creado" << endl;
    return 0;
}
*/