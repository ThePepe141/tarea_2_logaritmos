#include "structures.h"

int random_int(int i, int j){
    if (i==j){
        return i;
    }
    else{
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(i, j);
        return dis(gen);
    }
}

/*Generates a random number between (0,1]*/
double random_decimal(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(std::nextafter(0.0, 1.0), 1.0);
    return dis(gen);
}

int main(){

    int n_vertexs = 5;
    int n_edges = 6;
    vector<Node> vertexs;
    vertexs.resize(n_vertexs);
    vertexs[0] = 0;
    set<Edge> edges;
    //Fill "vertexs" and adds v-1 edges to "edges"
    for (int i=1; i<n_vertexs; i++){
        vertexs[i] = Node(i);
        if (i==1){
            edges.insert(Edge(random_decimal(), 0, 1));
        }
        else{
            edges.insert(Edge(random_decimal(), random_int(1, i-1), i));
        }

    }
    //fill the rest of "edges"
    while (edges.size() < n_edges) {
        int u = std::rand() % n_vertexs;
        int v = std::rand() % n_vertexs;

        if (u != v) { // make sure therea re not (u,u)
            // make sure there are not (u,v) and (v,u)
            Edge edge = u < v ? Edge(random_decimal(), u, v) : Edge(random_decimal(), v, u);
            if (edges.find(edge) == edges.end()) {
                edges.insert(edge);
            }
        }
    }    

    cout << "numero de vertices: " << n_vertexs << endl;
    cout << "numero de aristas: " << n_edges << endl;
    cout << "vertices: " << endl;
    for(int i=0; i<5; i++){
        cout << vertexs[i].key << endl;
    }

    cout << "aristas: " << endl;
    for (const auto& edge : edges) {
        std::cout << "(" << edge.weight << edge.node1.key << ", " << edge.node2.key << ")" << std::endl;
    }

    return 0;
}