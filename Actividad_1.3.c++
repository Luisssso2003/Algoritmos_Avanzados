#include <iostream>
#include <vector>
using namespace std;

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

// Función que resuelve el laberinto utilizando ramificación y poda
bool solucionarLaberintoRamificacionPoda(vector<vector<bool>>& laberinto, vector<vector<bool>>& solucion, int x, int y, int m, int n) {
    // Comprobar si hemos llegado a la salida
    if (x == m - 1 && y == n - 1) {
        solucion[x][y] = true;
        return true;
    }

    // Comprobar si la casilla actual es válida
    if (x >= 0 && x < m && y >= 0 && y < n && laberinto[x][y] && !solucion[x][y]) {
        // Marcar la casilla como visitada
        solucion[x][y] = true;

        // Explorar las cuatro direcciones posibles
        if (solucionarLaberintoRamificacionPoda(laberinto, solucion, x + 1, y, m, n) ||  // Abajo
            solucionarLaberintoRamificacionPoda(laberinto, solucion, x, y + 1, m, n) ||  // Derecha
            solucionarLaberintoRamificacionPoda(laberinto, solucion, x - 1, y, m, n) ||  // Arriba
            solucionarLaberintoRamificacionPoda(laberinto, solucion, x, y - 1, m, n)) {  // Izquierda
            return true;
        }

        // Si no se encuentra solución, desmarcar la casilla
        solucion[x][y] = false;
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

    // Resolver el laberinto utilizando backtracking
    vector<vector<bool>> solucionBacktracking(m, vector<bool>(n, false));
    if (solucionarLaberintoBacktracking(laberinto, solucionBacktracking, 0, 0)) {
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

    // Resolver el laberinto utilizando ramificación y poda
    vector<vector<bool>> solucionRamificacionPoda(m, vector<bool>(n, false));
    if (solucionarLaberintoRamificacionPoda(laberinto, solucionRamificacionPoda, 0, 0, m, n)) {
        cout << "Solución utilizando ramificación y poda:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << solucionRamificacionPoda[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No se encontró solución utilizando ramificación y poda." << endl;
    }

    return 0;
}
