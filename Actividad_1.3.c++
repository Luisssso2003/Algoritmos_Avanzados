#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <chrono>  // Incluimos la biblioteca para medir el tiempo
using namespace std;
using namespace std::chrono;

// Estructura para almacenar la posición y el camino recorrido
struct Nodo {
    int x, y;
    vector<vector<bool>> camino;
};

// Función que resuelve el laberinto utilizando backtracking
bool solucionarLaberintoBacktracking(vector<vector<bool>>& laberinto, vector<vector<bool>>& solucion, int x, int y) {
    // Comprobar si hemos llegado a la salida
    if (x == laberinto.size() - 1 && y == laberinto[0].size() - 1) {
        solucion[x][y] = true;
        return true;
    }

    // Comprobar si la casilla actual es válida
    if (x >= 0 && x < laberinto.size() && y >= 0 && y < laberinto[0].size() && laberinto[x][y] && !solucion[x][y]) {
        // Marcar la casilla como visitada
        solucion[x][y] = true;

        // Explorar las cuatro direcciones posibles
        if (solucionarLaberintoBacktracking(laberinto, solucion, x + 1, y) ||  // Abajo
            solucionarLaberintoBacktracking(laberinto, solucion, x, y + 1) ||  // Derecha
            solucionarLaberintoBacktracking(laberinto, solucion, x - 1, y) ||  // Arriba
            solucionarLaberintoBacktracking(laberinto, solucion, x, y - 1)) {  // Izquierda
            return true;
        }

        // Si no se encuentra solución, desmarcar la casilla
        solucion[x][y] = false;
    }

    // No se encontró solución
    return false;
}

// Función que resuelve el laberinto utilizando ramificación y poda con un stack
bool solucionarLaberintoRamificacionPodaConStack(vector<vector<bool>>& laberinto, vector<vector<bool>>& solucion, int m, int n) {
    stack<Nodo> s;
    s.push({0, 0, solucion});

    while (!s.empty()) {
        Nodo nodo = s.top();
        s.pop();

        int x = nodo.x;
        int y = nodo.y;
        solucion = nodo.camino;

        // Comprobar si hemos llegado a la salida
        if (x == m - 1 && y == n - 1) {
            solucion[x][y] = true;
            return true;
        }

        // Comprobar si la casilla actual es válida
        if (x >= 0 && x < m && y >= 0 && y < n && laberinto[x][y] && !solucion[x][y]) {
            // Marcar la casilla como visitada
            solucion[x][y] = true;

            // Agregar las rutas posibles al stack
            s.push({x + 1, y, solucion});  // Abajo
            s.push({x, y + 1, solucion});  // Derecha
            s.push({x - 1, y, solucion});  // Arriba
            s.push({x, y - 1, solucion});  // Izquierda
        }
    }

    // No se encontró solución
    return false;
}

int main() {
    int m, n;
    cin >> m >> n;

    // Leer el laberinto
    vector<vector<bool>> laberinto(m, vector<bool>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int value;
            cin >> value;
            laberinto[i][j] = (value == 1);
        }
    }

    // Ejecutar el algoritmo de backtracking
    vector<vector<bool>> solucionBacktracking(m, vector<bool>(n, false));
    auto startBacktracking = high_resolution_clock::now();
    if (solucionarLaberintoBacktracking(laberinto, solucionBacktracking, 0, 0)) {
        auto endBacktracking = high_resolution_clock::now();
        cout << "Solución utilizando backtracking:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << solucionBacktracking[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No se encontró solución utilizando backtracking." << endl;
    }

    // Primera ejecución de ramificación y poda con stack
    vector<vector<bool>> solucionRamificacionPoda(m, vector<bool>(n, false));
    auto start1 = high_resolution_clock::now();
    if (solucionarLaberintoRamificacionPodaConStack(laberinto, solucionRamificacionPoda, m, n)) {
        auto end1 = high_resolution_clock::now();
        cout << "Solución utilizando ramificación y poda con stack en la primera ejecución:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << solucionRamificacionPoda[i][j] << " ";
            }
            cout << endl;
        }
        auto duration1 = duration_cast<microseconds>(end1 - start1);
        cout << "Tiempo de ejecución en la primera ejecución: " << duration1.count() << " microsegundos." << endl;
    } else {
        cout << "No se encontró solución utilizando ramificación y poda con stack en la primera ejecución." << endl;
    }

    // Segunda ejecución de ramificación y poda con stack
    solucionRamificacionPoda.assign(m, vector<bool>(n, false));  // Reiniciar la solución
    auto start2 = high_resolution_clock::now();
    if (solucionarLaberintoRamificacionPodaConStack(laberinto, solucionRamificacionPoda, m, n)) {
        auto end2 = high_resolution_clock::now();
        cout << "Solución utilizando ramificación y poda con stack en la segunda ejecución:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << solucionRamificacionPoda[i][j] << " ";
            }
            cout << endl;
        }
        auto duration2 = duration_cast<microseconds>(end2 - start2);
        cout << "Tiempo de ejecución en la segunda ejecución: " << duration2.count() << " microsegundos." << endl;
    } else {
        cout << "No se encontró solución utilizando ramificación y poda con stack en la segunda ejecución." << endl;
    }

    return 0;
}
