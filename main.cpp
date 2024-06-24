#include "structures.cpp"
using namespace std;

int main() {
    vector<int> v_values = {1 << 10, 1 << 12, 1 << 14};
    vector<int> e_values = {1 << 16, 1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 21, 1 << 22};
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
                dijkstraFibonacci(graph, 0);
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

"""
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
"""