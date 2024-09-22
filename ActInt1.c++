#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

// Función para leer un archivo y retornar su contenido como un string
std::string leerArchivo(const std::string& filename) {
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // Eliminar espacios y saltos de línea
    content.erase(std::remove_if(content.begin(), content.end(), ::isspace), content.end());
    return content;
}

// Función para verificar si un código está contenido en la transmisión
bool contieneSubcadena(const std::string& transmission, const std::string& code, size_t& pos) {
    pos = transmission.find(code);
    return pos != std::string::npos;
}

std::pair<int, int> encontrarSubcadenaMasLarga(const std::string& str1, const std::string& str2, int& maxLength) {
    int m = str1.size(), n = str2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
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
    std::string transmission1 = leerArchivo("transmission1.txt");
    std::string transmission2 = leerArchivo("transmission2.txt");
    std::string mcode1 = leerArchivo("mcode1.txt");
    std::string mcode2 = leerArchivo("mcode2.txt");
    std::string mcode3 = leerArchivo("mcode3.txt");

    size_t pos;

    // Parte 1: Verificar si los códigos maliciosos están en las transmisiones
    std::cout << (contieneSubcadena(transmission1, mcode1, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;
    std::cout << (contieneSubcadena(transmission1, mcode2, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;
    std::cout << (contieneSubcadena(transmission1, mcode3, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;
    std::cout << (contieneSubcadena(transmission2, mcode1, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;
    std::cout << (contieneSubcadena(transmission2, mcode2, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;
    std::cout << (contieneSubcadena(transmission2, mcode3, pos) ? "true " + std::to_string(pos + 1) : "false") << std::endl;

    int maxLength = 0;
    auto posiciones = encontrarSubcadenaMasLarga(transmission1, transmission2, maxLength);

    if (maxLength > 0) {
        std::cout << "El substring común más largo tiene longitud: " << maxLength << std::endl;
        std::cout << "Posición inicial en transmission1: " << posiciones.first << std::endl;
        std::cout << "Posición final en transmission1: " << posiciones.second << std::endl;
        std::string substringComun = transmission1.substr(posiciones.first - 1, maxLength);
        std::cout << "El substring común más largo es: " << substringComun << std::endl;
    } else {
        std::cout << "No hay un substring común entre las transmisiones." << std::endl;
    }

    return 0;
}
