// C++ program to demonstrate the use of list containers
#include <iostream>
#include <list>
using namespace std;
using Pair = std::pair<int, double>; 
class graph{
    int V;
  	list<Pair> *l;
public:
    graph(int V){
        this->V = V;
        l = new list<Pair>[V];
    }
    void addEdge(int x, int y, double w){
        l[x].push_back(make_pair(y,w));
		l[y].push_back(make_pair(x,w));
    }
    void printAdj(){
        for (int i = 0; i < V; i++){
            cout << "Vertex "<< i << "\n";
            for (const auto& pair : l[i]) {
        	    std::cout << "  (" << pair.first << ", " << pair.second << ")\n";
            }
        }
    }
};
int main()
{
	graph g(5);
    g.addEdge(0,1,1.1);
    g.addEdge(0,2,2.1);
    g.addEdge(2,1,3.1);
    g.printAdj();
    g.addEdge(3,4,4.1);
}
