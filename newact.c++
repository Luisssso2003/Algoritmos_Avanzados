#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Función para calcular la distancia Euclidiana
double euclidean_distance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2)); // formula de distancia euclidiana
    // pow 2 eleva al cuadrado, sqrt es la raiz cuadrada y esto da la discatancia euclidiana
}

// Función para colorear el grafo con el agloritmo Welsh-Powell
vector<int> graph_coloring(vector<vector<int>>& graph, int n) { // toma el grafo y el numero de nodos, retorna un vector de colores
    vector<int> colors(n, -1); // crea un vector de colores de tamaño n, inicializado en -1, porque inicialmente no tiene color
    vector<bool> available_colors(n, true); // Rastrea colores disponibles para cada nodo

    // Ordenar nodos por grado en orden decreciente
    vector<int> nodes(n); // Crea un vector nodes que contiene los índices que son cada uno de los nodos del grafo no ordenados 
    for (int i = 0; i < n; ++i) nodes[i] = i;  // Llena el vector nodes con los índices de los nodos no ordenados
    sort(nodes.begin(), nodes.end(), [&](int a, int b) { // sort que ordena los nodos por grado en orden decreciente
        return graph[a].size() > graph[b].size(); // compara la cantidad de vecinos de cada nodo
    });

    // Asignar colores
    for (int node : nodes) { // bucle para recorrer los nodos ordenados por grado
        // Marcar colores usados por los vecinos
        for (int neighbor : graph[node]) { // se recorren todos los vecinos del nodo actual en el grafo
            if (colors[neighbor] != -1) { // si el vecino ya tiene un color asignado
                available_colors[colors[neighbor]] = false; // se marca el color como no disponible
                // asegura que el nodo no tome un color que ya esté siendo utilizado por algún vecino adyacente
            }
        }

        // Asignar el primer color disponible
        for (int color = 0; color < n; ++color) { // bucle para recorrer los colores disponibles
            if (available_colors[color]) { // si el color esta disponible
                colors[node] = color; // asigna el color al nodo actual
                break;
            }
        }

        // Restaurar la disponibilidad de colores
        for (int neighbor : graph[node]) { // bucle para recorrer los vecinos del nodo actual
            if (colors[neighbor] != -1) { // si el vecino ya tiene un color asignado
                available_colors[colors[neighbor]] = true; // se marca el color como disponible
            }
        }
        // Como se está analizando un nodo a la vez, una vez que se asigna un color a un nodo, los colores que estaban "bloqueados" 
        // por sus vecinos pueden ser restaurados para ser utilizados por otros nodos que aún no han sido coloreados.
    }

    return colors;
}

// Función principal para resolver el problema
int min_towers_to_destroy(int n, int d, vector<pair<int, int>>& towers) {
    // Construir el grafo con un vector de vectores, cada elemento es una torre (nodo) y sus vecinos
    vector<vector<int>> graph(n);
    // Agregar aristas al grafo basado en las distancias euclidianas entre las torres
    for (int i = 0; i < n; ++i) { // bucle para recorrer las torres
        for (int j = i + 1; j < n; ++j) {  // bucle para recorrer las torres que vienen despues de la torre actual i
        // es j + i porque la distancia es simetrica, no necesitas compararla 2 veces, evita calculos repetidos
            if (euclidean_distance(towers[i], towers[j]) <= d) { // calcular la distancia euclidiana entre las torres i y j
        // si el resultado es menor o igual a d, significa que las torres interfieren entre si
                graph[i].push_back(j); // agregas la torre de indice j a la lista de vecinos de la torre i
                graph[j].push_back(i); // agregas la torre de indice i a la lista de vecinos de la torre j
            }
        }
    }

    // Colorear el grafo
    vector<int> colors = graph_coloring(graph, n);

    // Contar nodos por color
    unordered_map<int, int> color_count; // unordered map almacena pares clave valor, la clave es el color del nodo y el valor
    // es la cantidad de nodos que tienen ese color
    for (int color : colors) { // el valor en la posición i de colors representa el color del nodo i.
        color_count[color]++; // se incrementa el contador de nodos con ese color
    }

    // Encontrar el color más frecuente
    int max_color_count = 0; // inicializa el contador de nodos con el color mas frecuente en 0
    for (auto& entry : color_count) { // bucle para recorrer los colores y la cantidad de nodos con ese color
        max_color_count = max(max_color_count, entry.second); // se actualiza el contador de nodos con el color mas frecuente
    }

    // Número de nodos a eliminar
    return n - max_color_count;
}

int main() { // funcion principal del programa
    // Entrada de numero de torres (n) y distancia maxima de interferencia (d)
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> towers(n); // vector de torres que cada elemento es el par de coordenadas de las torres
    for (int i = 0; i < n; ++i) { 
        cin >> towers[i].first >> towers[i].second; // bucle para asignar las coordenadas a cada torre
    }

    // funcion que retorna el numero minimo de torres a destruir
    cout << min_towers_to_destroy(n, d, towers) << endl;

    return 0;
}
