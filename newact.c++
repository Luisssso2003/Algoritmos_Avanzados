#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Función para calcular la distancia Euclidiana
double euclidean_distance(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// Función para colorear el grafo
vector<int> graph_coloring(vector<vector<int>>& graph, int n) {
    vector<int> colors(n, -1); // -1 indica que no está coloreado
    vector<bool> available_colors(n, true); // Rastrea colores disponibles

    // Ordenar nodos por grado en orden decreciente
    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) nodes[i] = i;
    sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return graph[a].size() > graph[b].size();
    });

    // Asignar colores
    for (int node : nodes) {
        // Marcar colores usados por los vecinos
        for (int neighbor : graph[node]) {
            if (colors[neighbor] != -1) {
                available_colors[colors[neighbor]] = false;
            }
        }

        // Asignar el primer color disponible
        for (int color = 0; color < n; ++color) {
            if (available_colors[color]) {
                colors[node] = color;
                break;
            }
        }

        // Restaurar la disponibilidad de colores
        for (int neighbor : graph[node]) {
            if (colors[neighbor] != -1) {
                available_colors[colors[neighbor]] = true;
            }
        }
    }

    return colors;
}

// Función principal para resolver el problema
int min_towers_to_destroy(int n, int d, vector<pair<int, int>>& towers) {
    // Construir el grafo
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (euclidean_distance(towers[i], towers[j]) <= d) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // Colorear el grafo
    vector<int> colors = graph_coloring(graph, n);

    // Contar nodos por color
    unordered_map<int, int> color_count;
    for (int color : colors) {
        color_count[color]++;
    }

    // Encontrar el color más frecuente
    int max_color_count = 0;
    for (auto& entry : color_count) {
        max_color_count = max(max_color_count, entry.second);
    }

    // Número de nodos a eliminar
    return n - max_color_count;
}

int main() {
    // Entrada
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> towers(n);
    for (int i = 0; i < n; ++i) {
        cin >> towers[i].first >> towers[i].second;
    }

    // Resolución
    cout << min_towers_to_destroy(n, d, towers) << endl;

    return 0;
}