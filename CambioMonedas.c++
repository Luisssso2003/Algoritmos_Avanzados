#include <iostream>    // Incluye la librería para entrada y salida estándar
#include <vector>      // Incluye la librería para usar el contenedor vector
#include <algorithm>   // Incluye la librería para funciones como sort
#include <limits.h>    // Incluye la librería para usar INT_MAX

using namespace std;   // Usa el espacio de nombres estándar para evitar escribir std:: cada vez

// Función para calcular el cambio utilizando el algoritmo avaro
void calculateChange(int change, const vector<int>& coins, vector<int>& coinCount) {
    // Itera sobre cada denominación de moneda
    for (int i = 0; i < coins.size(); ++i) {
        // Calcula cuántas monedas de la denominación actual se pueden usar
        coinCount[i] = change / coins[i];
        // Actualiza el valor restante del cambio
        change %= coins[i];
    }
}

// Función para calcular el cambio utilizando programación dinámica
void dynamicChange(int change, const vector<int>& coins, vector<int>& minCoins) {
    // Vector para almacenar el número mínimo de monedas necesarias para cada valor de cambio
    vector<int> dp(change + 1, INT_MAX);
    // Vector para rastrear la última moneda utilizada para alcanzar cada valor de cambio
    vector<int> lastCoin(change + 1, -1);

    // Se necesita 0 monedas para el cambio 0
    dp[0] = 0;

    // Llenar el vector dp con el número mínimo de monedas para cada valor de cambio
    for (int i = 1; i <= change; ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            // Verifica si la denominación actual puede ser utilizada
            if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                // Actualiza dp[i] si se encuentra una mejor solución (menos monedas)
                if (dp[i] > dp[i - coins[j]] + 1) {
                    dp[i] = dp[i - coins[j]] + 1;
                    lastCoin[i] = j; // Guarda la última moneda utilizada
                }
            }
        }
    }

    // Reconstruir la solución usando el vector lastCoin
    int amount = change;
    while (amount > 0 && lastCoin[amount] != -1) {
        minCoins[lastCoin[amount]]++;
        amount -= coins[lastCoin[amount]];
    }
}

int main() {
    int N, P, Q;
    
    // Solicitar el número de denominaciones
    cout << "Ingrese el número de denominaciones de monedas: ";
    cin >> N;
    vector<int> coins(N); // Crear un vector para almacenar las denominaciones

    // Solicitar las denominaciones de monedas
    cout << "Ingrese las denominaciones de las monedas (de mayor a menor):" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> coins[i];
    }

    // Solicitar el precio del producto y el monto pagado
    cout << "Ingrese el precio del producto: ";
    cin >> P;
    cout << "Ingrese el monto con el que se paga: ";
    cin >> Q;
    int change = Q - P; // Calcular el cambio a devolver

    // Mostrar el cambio que se debe devolver
    cout << "Cambio a devolver: " << change << endl;

    // Ordenar las denominaciones de mayor a menor para el algoritmo avaro
    sort(coins.rbegin(), coins.rend());

    vector<int> greedyCoins(N, 0); // Vector para almacenar el número de monedas en el enfoque avaro
    vector<int> dynamicCoins(N, 0); // Vector para almacenar el número de monedas en el enfoque de programación dinámica

    // Calcular el cambio usando el algoritmo avaro
    calculateChange(change, coins, greedyCoins);
    // Calcular el cambio usando la programación dinámica
    dynamicChange(change, coins, dynamicCoins);

    // Mostrar los resultados del algoritmo avaro
    cout << "Algoritmo Avaro:" << endl;
    for (int count : greedyCoins) {
        cout << count << endl;
    }

    // Mostrar los resultados de la programación dinámica
    cout << "Programación Dinámica:" << endl;
    for (int count : dynamicCoins) {
        cout << count << endl;
    }

    return 0; // Fin del programa
}
