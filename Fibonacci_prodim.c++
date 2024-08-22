#include <iostream>
#include <vector>

using namespace std;

void fibonacci(int n) {
    // Paso 1: Crear un vector para almacenar los resultados intermedios
    vector<int> fib(n + 1);

    // Paso 2: Inicializar los primeros valores de la serie
    fib[0] = 0;
    fib[1] = 1;

    // Paso 3: Calcular y llenar el vector con los valores de Fibonacci
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Paso 4: Mostrar la secuencia completa
    cout << "Secuencia de Fibonacci hasta " << n << ": ";
    for (int i = 0; i <= n; i++) {
        cout << fib[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Ingrese un número: ";
    cin >> n;
    fibonacci(n);
    return 0;
}