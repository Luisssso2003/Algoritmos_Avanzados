#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Función para leer un archivo y retornar su contenido como un string
string leerArchivo(const string& filename) {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    // Eliminar espacios y saltos de línea
    content.erase(remove_if(content.begin(), content.end(), ::isspace), content.end());
    return content;
}

// Función para verificar si un código está contenido en la transmisión
bool contieneSubcadena(const string& transmission, const string& code, size_t& pos) {
    pos = transmission.find(code);
    return pos != string::npos;
}

// Función para encontrar el palíndromo más largo dentro de una cadena
pair<int, int> encontrarPalindromoMasLargo(const string& s) {
    int n = s.size();
    if (n == 0) return {0, 0};

    int inicio = 0, maxLen = 1;

    // Crear una tabla para la búsqueda dinámica
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Todos los caracteres individuales son palíndromos
    for (int i = 0; i < n; ++i)
        dp[i][i] = true;

    // Verificar pares de caracteres consecutivos
    for (int i = 0; n > 1 && i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            inicio = i;
            maxLen = 2;
        }
    }

    // Verificar subcadenas más largas
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                inicio = i;
                maxLen = len;
            }
        }
    }

    return {inicio + 1, inicio + maxLen};  // Retorna la posición 1-indexada
}

// Función para encontrar el substring común más largo entre dos cadenas
pair<int, int> encontrarSubcadenaMasLarga(const string& str1, const string& str2, int& maxLength) {
    int m = str1.size(), n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int finPos = 0;
    maxLength = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    finPos = i;  // Corrige el cálculo de finPos
                }
            }
        }
    }
    int startPos = finPos - maxLength;
    return {startPos + 1, finPos};  // Devuelve las posiciones correctas
}

int main() {
    // Leer las transmisiones y códigos maliciosos desde archivos
    string transmission1 = leerArchivo("transmission1.txt");
    string transmission2 = leerArchivo("transmission2.txt");
    string mcode1 = leerArchivo("mcode1.txt");
    string mcode2 = leerArchivo("mcode2.txt");
    string mcode3 = leerArchivo("mcode3.txt");

    size_t pos;

    // Parte 1: Verificar si los códigos maliciosos están en las transmisiones
    cout << "Transmision 1 contiene Mcode1: " << (contieneSubcadena(transmission1, mcode1, pos) ? "true " + to_string(pos + 1) : "false") << endl;
    cout << "Transmision 1 contiene Mcode2: " << (contieneSubcadena(transmission1, mcode2, pos) ? "true " + to_string(pos + 1) : "false") << endl;
    cout << "Transmision 1 contiene Mcode3: " << (contieneSubcadena(transmission1, mcode3, pos) ? "true " + to_string(pos + 1) : "false") << endl;
    cout << "Transmision 2 contiene Mcode1: " << (contieneSubcadena(transmission2, mcode1, pos) ? "true " + to_string(pos + 1) : "false") << endl;
    cout << "Transmision 2 contiene Mcode2: " << (contieneSubcadena(transmission2, mcode2, pos) ? "true " + to_string(pos + 1) : "false") << endl;
    cout << "Transmision 2 contiene Mcode3: " << (contieneSubcadena(transmission2, mcode3, pos) ? "true " + to_string(pos + 1) : "false") << endl;

    // Parte 2: Encontrar y mostrar el palíndromo más largo en cada transmisión
    auto palindromoTrans1 = encontrarPalindromoMasLargo(transmission1);
    auto palindromoTrans2 = encontrarPalindromoMasLargo(transmission2);
    
    cout << "Palindromo más largo en Transmision 1 comienza en " << palindromoTrans1.first << " y termina en " << palindromoTrans1.second << endl;
    cout << "Palindromo más largo en Transmision 2 comienza en " << palindromoTrans2.first << " y termina en " << palindromoTrans2.second << endl;

    // Parte 3: Encontrar el substring común más largo entre ambas transmisiones
    int maxLength = 0;
    auto posiciones = encontrarSubcadenaMasLarga(transmission1, transmission2, maxLength);

    if (maxLength > 0) {
        cout << "Substring común más largo comienza en " << posiciones.first << " y termina en " << posiciones.second << " en Transmision 1" << endl;
        
        // Extraer y mostrar el substring común más largo
        string substringComun = transmission1.substr(posiciones.first - 1, posiciones.second - posiciones.first + 1);
        cout << "El substring común más largo es: " << substringComun << endl;
    } else {
        cout << "No hay un substring común entre las transmisiones." << endl;
    }

    return 0;
}
