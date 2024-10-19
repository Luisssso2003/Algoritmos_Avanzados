#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring> // Para memset

using namespace std;

const int INF = numeric_limits<int>::max();

// Función para resolver el problema del viajero usando el algoritmo del mejor más próximo
void problemaDelViajero(const vector<vector<int>>& distancias, int N) {
    vector<bool> visitado(N, false); // Vector para marcar las colonias visitadas
    vector<int> ruta; // Vector para almacenar la ruta
    int actual = 0;  // Empezamos desde la colonia 'A'
    int totalDistancia = 0;
    
    visitado[actual] = true;
    ruta.push_back(actual);

    for (int i = 1; i < N; ++i) {
        int ciudadMasCercana = -1;
        int distanciaMinima = INF;

        // Buscar la colonia más cercana no visitada
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

    // Volver a la colonia de origen
    totalDistancia += distancias[actual][0];
    ruta.push_back(0);

    // Mostrar la ruta y la distancia total
    cout << "Ruta más corta para visitar todas las colonias:" << endl;
    for (int i = 0; i < ruta.size(); ++i) {
        cout << char('A' + ruta[i]);
        if (i < ruta.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "Distancia total: " << totalDistancia << endl;
}

// Implementación del algoritmo de Edmonds-Karp para flujo máximo
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
                    return true; // Encontramos un camino aumentante
                }
            }
        }
    }
    return false; // No encontramos más caminos aumentantes
}

int edmondsKarp(const vector<vector<int>>& capacidad, int fuente, int sumidero, int N) {
    vector<vector<int>> capacidadResidual = capacidad;
    vector<int> parent(N); // rastrear el camino aumentante.
    int flujoMaximo = 0;

    // Mientras exista un camino aumentante
    while (bfs(capacidadResidual, parent, fuente, sumidero, N)) {
        int flujoAumentante = INF;

        // Encontrar la capacidad mínima en el camino aumentante
        for (int v = sumidero; v != fuente; v = parent[v]) {
            int u = parent[v];
            flujoAumentante = min(flujoAumentante, capacidadResidual[u][v]);
        }

        // Actualizar capacidades residuales
        for (int v = sumidero; v != fuente; v = parent[v]) {
            int u = parent[v];
            capacidadResidual[u][v] -= flujoAumentante;
            capacidadResidual[v][u] += flujoAumentante; // Inverso
        }

        flujoMaximo += flujoAumentante;
    }

    return flujoMaximo;
}

int main() {
    int N;
    cin >> N;
    
    // Recibir la matriz de distancias
    vector<vector<int>> distancias(N, vector<int>(N));
    
    // Leer la matriz de distancias
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            cin >> distancias[i][j];

    // Resolver el problema del viajero (ruta más corta)
    problemaDelViajero(distancias, N);

    // Recibir la matriz de capacidades de transmisión
    vector<vector<int>> capacidad(N, vector<int>(N));
    
    // Leer la matriz de capacidad de flujo
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            cin >> capacidad[i][j];

    // Definir el nodo fuente y sumidero
    int fuente = 0; // Nodo inicial (A)
    int sumidero = N - 1; // Nodo final (última colonia, Z, B, etc.)

    // Calcular el flujo máximo de información entre la colonia fuente y la colonia sumidero
    int flujoMaximo = edmondsKarp(capacidad, fuente, sumidero, N);

    // Mostrar el flujo máximo
    cout << "Flujo máximo de información del nodo inicial al nodo final: " << flujoMaximo << endl;

    return 0;
}
