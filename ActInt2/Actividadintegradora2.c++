#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Arco {
    int u, v, peso;
    bool operator<(const Arco& other) const {
        return peso < other.peso;
    }
};

void problemaDelViajero(const vector<vector<int>>& distancias, int N) {
    vector<bool> visitado(N, false);
    vector<int> ruta;
    int actual = 0;
    int totalDistancia = 0;
    
    visitado[actual] = true;
    ruta.push_back(actual);

    for (int i = 1; i < N; ++i) {
        int ciudadMasCercana = -1;
        int distanciaMinima = INF;

        for (int j = 0; j < N; ++j) {
            if (!visitado[j] && distancias[actual][j] < distanciaMinima) {
                distanciaMinima = distancias[actual][j];
                ciudadMasCercana = j;
            }
        }

        visitado[ciudadMasCercana] = true;
        ruta.push_back(ciudadMasCercana);
        totalDistancia += distanciaMinima;
        actual = ciudadMasCercana;
    }

    totalDistancia += distancias[actual][0];
    ruta.push_back(0);

    cout << "2. Ruta a seguir por el personal que reparte correspondencia:" << endl;
    for (int i = 0; i < ruta.size(); ++i) {
        cout << char('A' + ruta[i]);
        if (i < ruta.size() - 1) cout << " -> ";
    }
    cout << endl;
}

bool bfs(const vector<vector<int>>& capacidadResidual, vector<int>& parent, int fuente, int sumidero, int N) {
    vector<bool> visitado(N, false);
    queue<int> q;
    q.push(fuente);
    visitado[fuente] = true;
    parent[fuente] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < N; ++v) {
            if (!visitado[v] && capacidadResidual[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visitado[v] = true;
                if (v == sumidero) {
                    return true;
                }
            }
        }
    }
    return false;
}

int edmondsKarp(const vector<vector<int>>& capacidad, int fuente, int sumidero, int N) {
    vector<vector<int>> capacidadResidual = capacidad;
    vector<int> parent(N);
    int flujoMaximo = 0;

    while (bfs(capacidadResidual, parent, fuente, sumidero, N)) {
        int flujoAumentante = INF;

        for (int v = sumidero; v != fuente; v = parent[v]) {
            int u = parent[v];
            flujoAumentante = min(flujoAumentante, capacidadResidual[u][v]);
        }

        for (int v = sumidero; v != fuente; v = parent[v]) {
            int u = parent[v];
            capacidadResidual[u][v] -= flujoAumentante;
            capacidadResidual[v][u] += flujoAumentante;
        }

        flujoMaximo += flujoAumentante;
    }

    return flujoMaximo;
}

int encontrar(int u, vector<int>& padre) {
    if (u == padre[u]) return u;
    return padre[u] = encontrar(padre[u], padre);
}

void unir(int u, int v, vector<int>& padre) {
    padre[encontrar(u, padre)] = encontrar(v, padre);
}

void kruskalMST(const vector<vector<int>>& distancias, int N) {
    vector<Arco> arcos;
    
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (distancias[i][j] != 0) {
                arcos.push_back({i, j, distancias[i][j]});
            }
        }
    }
    
    sort(arcos.begin(), arcos.end());

    vector<int> padre(N);
    for (int i = 0; i < N; ++i) padre[i] = i;

    vector<Arco> mst;
    for (const auto& arco : arcos) {
        if (encontrar(arco.u, padre) != encontrar(arco.v, padre)) {
            unir(arco.u, arco.v, padre);
            mst.push_back(arco);
        }
    }

    cout << "1. Forma de cablear las colonias con fibra:" << endl;
    for (const auto& arco : mst) {
        cout << "(" << char('A' + arco.u) << "," << char('A' + arco.v) << ") ";
    }
    cout << endl;
}

void encontrarCentralMasCercana(const vector<vector<int>>& distancias, int N) {
    vector<int> sumaDistancias(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sumaDistancias[i] += distancias[i][j];
        }
    }

    int centralMasCercana = min_element(sumaDistancias.begin(), sumaDistancias.end()) - sumaDistancias.begin();
    
    cout << "4. La colonia más céntrica (que podría ser la mejor ubicación para una central) es: " 
         << char('A' + centralMasCercana) << endl;
}

int main() {
    int N;
    cin >> N;
    
    vector<vector<int>> distancias(N, vector<int>(N));
    
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            cin >> distancias[i][j];

    vector<vector<int>> capacidad(N, vector<int>(N));
    
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            cin >> capacidad[i][j];

    kruskalMST(distancias, N);

    problemaDelViajero(distancias, N);

    int fuente = 0;
    int sumidero = N - 1;

    int flujoMaximo = edmondsKarp(capacidad, fuente, sumidero, N);

    cout << "3. Valor de flujo máximo de información del nodo inicial al nodo final: " << flujoMaximo << endl;

    encontrarCentralMasCercana(distancias, N);

    return 0;
}