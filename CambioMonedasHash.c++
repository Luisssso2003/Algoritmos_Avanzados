#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits.h>
#include <algorithm>

using namespace std;

// Función para calcular el cambio utilizando el algoritmo avaro
void calculateChange(int change, const vector<int>& coins, vector<int>& coinCount) {
    for (int i = 0; i < coins.size(); ++i) {
        coinCount[i] = change / coins[i];
        change %= coins[i];
    }
}

// Función para calcular el cambio utilizando programación dinámica con hash
void dynamicChange(int change, const vector<int>& coins, unordered_map<int, int>& minCoins) {
    vector<int> dp(change + 1, INT_MAX); // Inicializa el vector dp con valores máximos
    vector<int> lastCoin(change + 1, -1); // Para rastrear la última moneda utilizada

    dp[0] = 0; // Se necesitan 0 monedas para el cambio 0

    for (int i = 1; i <= change; ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                if (dp[i] > dp[i - coins[j]] + 1) {
                    dp[i] = dp[i - coins[j]] + 1;
                    lastCoin[i] = j; // Guarda la última moneda utilizada
                }
            }
        }
    }

    int amount = change;
    while (amount > 0 && lastCoin[amount] != -1) {
        minCoins[coins[lastCoin[amount]]]++;
        amount -= coins[lastCoin[amount]];
    }
}

int main() {
    int N; // Número de denominaciones
    cout << "Ingrese la cantidad de denominaciones: ";
    cin >> N;

    vector<int> coins(N); // Vector para las denominaciones
    cout << "Ingrese las denominaciones en orden de mayor a menor:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> coins[i];
    }

    int P, Q; // Precio del producto y billete con el que se paga
    cout << "Ingrese el precio del producto: ";
    cin >> P;
    cout << "Ingrese el billete con el que se paga: ";
    cin >> Q;

    int change = Q - P; // Calcula el cambio a devolver

    cout << "Cambio a devolver: " << change << endl;

    // Ordenar denominaciones de mayor a menor
    sort(coins.rbegin(), coins.rend());

    vector<int> greedyCoins(N, 0); // Vector para el algoritmo avaro
    unordered_map<int, int> dynamicCoins; // Usamos unordered_map para la programación dinámica

    // Calcular el cambio usando el algoritmo avaro
    calculateChange(change, coins, greedyCoins);
    // Calcular el cambio usando la programación dinámica con hash
    dynamicChange(change, coins, dynamicCoins);

    // Mostrar los resultados del algoritmo avaro
    cout << "Algoritmo Avaro:" << endl;
    for (int i = 0; i < N; ++i) {
        if (greedyCoins[i] > 0)
            cout << coins[i] << ": " << greedyCoins[i] << endl;
    }

    // Mostrar los resultados de la programación dinámica
    cout << "Programación Dinámica:" << endl;
    for (const auto& pair : dynamicCoins) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
