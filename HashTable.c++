#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Definición de la clase HashTable que implementa una tabla hash.
class HashTable {
private:
    int INITIAL_CAPACITY = 10;  // Capacidad inicial de la tabla
    float LOAD_FACTOR = 0.80;  // Factor de carga máximo antes de redimensionar
    int capacity;  // Capacidad actual de la tabla
    int itemCount;  // Número de elementos en la tabla
    vector<list<pair<int, string>>> table;  // Tabla hash, almacenada como un vector de listas de pares (clave, valor)

    // Función hash que calcula el índice de la tabla a partir de la clave
    int hashFunction(int key) {
        return key % capacity;
    }

    // Redimensiona la tabla cuando el factor de carga se excede
    void resize() {
    int newCapacity = capacity * 1.8; // Aumenta la capacidad en un 80%
    vector<list<pair<int, string>>> newTable(newCapacity); // Se crea una nueva hash table

    // Reubica todos los elementos de la tabla vieja a la nueva
    // este for recorre cada bucket de la hash table anterior
    for (int i = 0; i < table.size(); i++) {
        list<pair<int, string>>& bucket = table[i];  // bucket viejo hace referencia directa a 
        // uno de los buckets de la nueva tabla hashs
        // este for recorre cada elemento en la lista (es decir, cada par clave-valor) dentro del bucket actual.
        for (const pair<int, string>& item : bucket) { // item es una referencia constante a cada par pair<int, string> dentro del bucket.
            int newIndex = item.first % newCapacity; // es la clave del par actual (item), y se utiliza para calcular el nuevo índice 
            // en la tabla hash con la nueva capacidad 
            newTable[newIndex].push_back(item);
            // el par actual (item) se agrega al bucket correspondiente en la nueva tabla hash
            }
        }
    // Asigna la nueva tabla y actualiza la capacidad
    table = move(newTable); // move convierte un objeto en un rvalue, permitiendo la transferencia eficiente de recursos.
    capacity = newCapacity;
    }

public:
    // Constructor que inicializa la tabla hash con la capacidad inicial y un contador de elementos a cero
    HashTable() : capacity(INITIAL_CAPACITY), itemCount(0) {
        table.resize(capacity); // 
    }

    // Verifica si la tabla está vacía
    bool isEmpty() const {
        return itemCount == 0;
    }

    // Inserta un nuevo par clave-valor en la tabla
    void insertItem(int key, string value) {
    if ((float)(itemCount + 1) / capacity > LOAD_FACTOR) {
        resize();
    }
    
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    
    // Simplemente añadimos el nuevo par clave-valor al final de la lista
    cell.emplace_back(key, value);
    itemCount++;
    
    cout << "[INFO] Item inserted." << endl;
    }

    // Elimina un elemento de la tabla usando la clave
    void removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyFound = false;

    while (bItr != end(cell)) {
        if (bItr->first == key) {
            bItr = cell.erase(bItr);
            itemCount--;
            keyFound = true;
        } else {
            ++bItr;
        }
    }

    if (keyFound) {
        cout << "[INFO] Item(s) removed." << endl;
    } else {
        cout << "[WARNING] Key not found. Nothing removed." << endl;
    }
    }

    // Busca un valor en la tabla usando la clave
    vector<string> searchTable(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    vector<string> results;

    for (const auto& item : cell) {
        if (item.first == key) {
            results.push_back(item.second);
        }
    }

    if (results.empty()) {
        cout << "[INFO] Key not found." << endl;
    }

    return results;
    }

    // Imprime el contenido de la tabla
    void printTable() {
    for (int i = 0; i < capacity; i++) {
        if (table[i].empty()) continue;
        cout << "Bucket " << i << ":" << endl;
        for (const auto& item : table[i]) {
            cout << "  Key: " << item.first << " Value: " << item.second << endl;
        }
    }
    }

    // Retorna el número de elementos en la tabla
    int getSize() const {
        return itemCount;
    }

    // Retorna la capacidad actual de la tabla
    int getCapacity() const {
        return capacity;
    }
};

int main() {
    HashTable ht;

    // Inserciones iniciales
    ht.insertItem(905, "Jim");
    ht.insertItem(201, "Tom");
    ht.insertItem(332, "Bob");
    ht.insertItem(124, "Sally");
    ht.insertItem(123, "Morty");
    ht.insertItem(123, "Rick");  // Clave duplicada
    ht.insertItem(123, "Summer");  // Otra clave duplicada

    cout << "Table after insertions:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;

    // Eliminar elementos
    ht.removeItem(201);
    ht.removeItem(123);  // Esto debería eliminar todas las entradas con clave 123

    cout << "\nTable after removals:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;

    // Búsquedas
    cout << "\nSearch for key 905:" << endl;
    for (const auto& value : ht.searchTable(905)) {
        cout << value << endl;
    }

    cout << "\nSearch for key 123 (should be empty):" << endl;
    for (const auto& value : ht.searchTable(123)) {
        cout << value << endl;
    }

    // Insertar más elementos con la misma clave
    ht.insertItem(332, "Alice");
    ht.insertItem(332, "Eve");

    cout << "\nTable after inserting duplicates:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;
    return 0;
}