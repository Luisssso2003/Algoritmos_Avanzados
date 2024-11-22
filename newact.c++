#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;

// funcion para calcular la distancia euclidiana
double distancia_euclidiana(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2)); // formula de distancia euclidiana
}


// funcion para colorear el grafo con el agloritmo Welsh-Powell
vector<int> colorear_grafo(vector<vector<int>> grafo, int n){ // toma el grafo y el numero de nodos, regresa un vector de colores
    vector<int> colores(n, -1);  // crea un vector de colores de tamaño n, inicializado en -1 porque inicialmente no tiene color
    vector<bool> colores_disponibles(n, true); // crea un vector que rastrea colores disponibles para cada nodo


    // ordenar nodos por grado en orden decreciente
    vector<int> nodos(n);  // crea un vector que contiene los indices que son cada uno de los nodos del grafo no ordenados 
    for(int i = 0; i < n; i++){ // llena el vector nodos con los indices de los nodos no ordenados
        nodos[i] = i; 
        sort(nodos.begin(), nodos.end(), [&](int a, int b){ // sort que ordena los nodos por grado en orden decreciente
            return grafo[a].size() > grafo[b].size();
        });
    }

    // asignar colores
    for(int nodo : nodos){ // bucle para recorrer los nodos ordenados por grado
        for(int vecino : grafo[nodo]){ // se recorren todos los vecinos del nodo actual en el grafo
            if(colores[vecino] != -1){ // si el vecino ya tiene un color asignado
                colores_disponibles[colores[vecino]] = false; // se marca el color como no disponible
            }
        }

        // asignar el primer color disponible
        for(int color = 0; color < n; color++){
            if(colores_disponibles[color]){ // si el color esta disponible
                colores[nodo] = color; // asigna el color al nodo actual
                break;
            }
        }
        
        // restaurar la disponibilidad de colores
        for(int vecino : grafo[nodo]){ // bucle para recorrer los vecinos del nodo actual
            if(colores[vecino] != -1){ // si el vecino ya tiene un color asignado
                colores_disponibles[colores[vecino]] = true; // se marca el color como disponible
            }
        }
        return colores; // regresa el vector de colores
    }
}

// funcion para resolver el problema 
int torres_minimas_a_destruir(int n, int d, vector<pair<int, int>>& torres) {
    vector<vector<int>> grafo(n); // construir el grafo con un vector de vectores, cada elemento es una torre (nodo) y sus vecinos

    for(int i = 0; i < n; i++){ // bucle para recorrer todas las torres
        for(int j = i + 1; j < n; j++){
            if(distancia_euclidiana(torres[i], torres[j]) <= d){ // si la distancia entre las torres es menor o igual a d (interferencia)
                grafo[i].push_back(j); // se agrega la arista al grafo
                grafo[j].push_back(i);
            }
        }
    }

    vector<int> colores = colorear_grafo(grafo, n); // se llama la funcion para colorear el grafo con el algoritmo Welsh-Powell

    unordered_map<int, int> torres_por_color; // se crea un mapa para contar cuantas torres hay por color
    for(int color : colores){ // bucle para recorrer los colores
        torres_por_color[color]++; // se cuenta cuantas torres hay por color
    }

    int color_maximo = 0; // se inicializa el color maximo en 0
    for(auto par : torres_por_color){ // bucle para recorrer el mapa de torres por color
        color_maximo = max(color_maximo, par.second); // se actualiza el color maximo 
    }

    return n - color_maximo; // se regresa el numero minimo de torres a destruir
}

int main(){
    int n; 
    int d; 
     // entrada de numero de torres (n) y distancia maxima de interferencia (d)
    cin >> n >> d;

    vector<pair<int, int>> torres(n);  // vector de torres que cada elemento es el par de coordenadas de las torres
    for(int i = 0; i < n; i++){
        cin >> torres[i].first >> torres[i].second;
    }

    // funcion que regresa el numero minimo de torres a destruir
    cout << torres_minimas_a_destruir(n, d, torres) << endl;
    return 0;
}
