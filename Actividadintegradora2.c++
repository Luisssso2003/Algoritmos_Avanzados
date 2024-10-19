#include <iostream>
#include <vector>
#include <limits>

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

int main() {
    int N;
    cin >> N;
    
    // recibir la matriz de distancias
    vector<vector<int>> distancias(N, vector<int>(N));
    
    // leer la matriz de distancias
    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            cin >> distancias[i][j];

    // resolver el problema del viajero (ruta más corta) con el algoritmo del mejor más próximo 
    problemaDelViajero(distancias, N);

    return 0;
}
