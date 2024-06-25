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
    ofstream results("execution_times_minheap.csv");
    results << "v,e,time\n";

    for (int v : v_values) {
        for (int e : e_values) {
            vector<double> execution_times_minheap;
            int valor_e = 1 << e;
            int valor_v = 1 << v;
            if(valor_e > valor_v*(valor_v-1)/2){
                break;
            } // No se pueden tener más aristas que v*(v-1)/2 (grafo completo)
            for (int i = 0; i < grafnumber; ++i) {
                Graph g = createGraph(v,e);
                auto start = chrono::high_resolution_clock::now();
                dijkstra_heap(0, g);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                execution_times_minheap.push_back(duration.count());
            }

            double avg_time = accumulate(execution_times_minheap.begin(), execution_times_minheap.end(), 0.0) / execution_times_minheap.size();
            results << v << "," << e << "," << avg_time << "\n";
            cout << "Average execution time for v = " << v << " and e = " << e << " is " << avg_time << " seconds." << endl;
        }
    }

    results.close();
    return 0;
}
