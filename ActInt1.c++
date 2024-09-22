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

    return 0;
}
