#include<iostream>
#include<vector>
using namespace std;

class Graph{
    public:
    // agrega una arista a un grafo no dirigido usando una lista  de adyacencia
    void addEdge(vector<vector<int>> &adj, int s, int f){
    // &adj es una referencia a un vector de vectores de enteros, que representa la lista de adyacencia del grafo
        adj[s].push_back(f); 
        adj[f].push_back(s);
    // agrega el vertice f a la lista de adyacencia del vértice s y viceversa
    }

    // funcion recursiva que implementa el DFS
    void DFSrec(vector<vector<int>> &adj, vector<bool> &visited, int s){
        // vector booleano que lleva un registro de qué vertices ya han sido visitados
        visited[s] = true;
        cout << s << " ";
        // adj[v].size() da el número de vecinos que tiene el vértice s
        for(int i = 0; i < adj[s].size(); i++){
        // accede al i-esimo vecino del vértice s para ver si ha sido visitado
            if(!visited[adj[s][i]]){
        // la llamada recursiva pasa el mismo grafo, el mismo vector de visitados, y el vecino actual como nuevo vertice a explorar
                DFSrec(adj, visited, adj[s][i]);
            }
        }
    }

    // funcion que inicializa el vector de visitados y llama a la funcion recursiva
    void DFS(vector<vector<int>> &adj, int s){
        vector<bool> visited(adj.size(), false);
        DFSrec(adj, visited, s);
    };
};

int main(){
    int V = 6; // numero de vertices en el grafo

    // lista de adyacencia para el grafo
    vector<vector<int>> adj(V);

    // definir las aristas de los vertices
    vector<vector<int>> edges={{1, 2}, {1, 0}, {2, 0}, {2, 3}, {3, 5}, {4, 5}};

    Graph g;

    // llenar la lista de adyacencia con aristas del grafo
    for (auto &e : edges) // este bucle recorre todas las aristas definidas en edges
        g.addEdge(adj, e[0], e[1]); // para cada arista 'e', se llama al método addEdge

    int source = 1; // vertice inicial para el DFS
    cout << "DFS from source: " << source << endl;
    g.DFS(adj, source); // Hacer el DFS empezando en el vertice inicial
    return 0;
}