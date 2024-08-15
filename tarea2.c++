#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Definición de la clase HashTable que implementa una tabla hash.
class HashTable {
private:
    static const int INITIAL_CAPACITY = 10;  // Capacidad inicial de la tabla
    static const float LOAD_FACTOR;  // Factor de carga máximo antes de redimensionar
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
        newCapacity = newCapacity < 10 ? 10 : newCapacity; // Asegura una capacidad mínima de 10
        vector<list<pair<int, string>>> newTable(newCapacity);
        
        // Reubica todos los elementos de la tabla vieja a la nueva
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                int newIndex = pair.first % newCapacity;
                newTable[newIndex].push_back(pair);
            }
        }
        
        // Asigna la nueva tabla y actualiza la capacidad
        table = move(newTable);
        capacity = newCapacity;
    }

public:
    // Constructor que inicializa la tabla hash con la capacidad inicial y un contador de elementos a cero
    HashTable() : capacity(INITIAL_CAPACITY), itemCount(0) {
        table.resize(capacity);
    }

    // Verifica si la tabla está vacía
    bool isEmpty() const {
        return itemCount == 0;
    }

    // Inserta un nuevo par clave-valor en la tabla
    void insertItem(int key, string value) {
        // Redimensiona la tabla si se supera el factor de carga
        if ((float)(itemCount + 1) / capacity > LOAD_FACTOR) {
            resize();
        }
        
        int hashValue = hashFunction(key); // Calcula el índice de la tabla usando la función hash
        auto& cell = table[hashValue]; // Referencia al bucket correspondiente
        auto bItr = begin(cell);
        bool keyExists = false;

        // Recorre el bucket para verificar si la clave ya existe
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr->second = value; // Si la clave existe, reemplaza el valor
                cout << "[WARNING] Key exists. Value replaced." << endl;
                break;
            }
        }
        if (!keyExists) {
            cell.emplace_back(key, value); // Si la clave no existe, inserta el nuevo par clave-valor
            itemCount++;
        }
    }

    // Elimina un elemento de la tabla usando la clave
    void removeItem(int key) {
        int hashValue = hashFunction(key); // Calcula el índice de la tabla usando la función hash
        auto& cell = table[hashValue]; // Referencia al bucket correspondiente
        auto bItr = begin(cell);
        bool keyExists = false;

        // Recorre el bucket para encontrar la clave
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                keyExists = true;
                bItr = cell.erase(bItr); // Elimina el par clave-valor si la clave es encontrada
                itemCount--;
                cout << "[INFO] Item removed." << endl;
                break;
            }
        }
        if (!keyExists) {
            cout << "[WARNING] Key not found. Nothing removed." << endl;
        }
    }

    // Busca un valor en la tabla usando la clave
    string searchTable(int key) {
        int hashValue = hashFunction(key); // Calcula el índice de la tabla usando la función hash
        auto& cell = table[hashValue]; // Referencia al bucket correspondiente
        auto bItr = begin(cell);

        // Recorre el bucket para encontrar la clave
        for (; bItr != end(cell); bItr++) {
            if (bItr->first == key) {
                return bItr->second; // Retorna el valor asociado a la clave
            }
        }
        return "Key not found."; // Retorna un mensaje si la clave no es encontrada
    }

    // Imprime el contenido de la tabla
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].size() == 0) continue; // Omite los buckets vacíos
            auto bItr = table[i].begin();
            for (; bItr != table[i].end(); bItr++) {
                cout << "Key: " << bItr->first << " Value: " << bItr->second << endl; // Imprime cada par clave-valor
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

// Inicializa el factor de carga estático
const float HashTable::LOAD_FACTOR = 0.80f;

int main() {
    HashTable ht;

    // Verifica si la tabla está vacía
    if (ht.isEmpty()) {
        cout << "Correct Answer: Table is empty." << endl;
    } else {
        cout << "Incorrect Answer: Table is not empty." << endl;
    }

    // Inserciones para asegurar que se supere el factor de carga y se redimensione la tabla
    ht.insertItem(905, "Jim");
    ht.insertItem(201, "Tom");
    ht.insertItem(332, "Bob");
    ht.insertItem(124, "Sally");
    ht.insertItem(512, "Sue");
    ht.insertItem(632, "Shawn");
    ht.insertItem(422, "Tim");
    ht.insertItem(432, "Rob");
    ht.insertItem(111, "Rick");
    ht.insertItem(123, "Morty");

    // Agregamos más elementos para asegurarnos de que el factor de carga se supere
    ht.insertItem(543, "John");
    ht.insertItem(654, "Alice");
    ht.insertItem(765, "Eve");
    ht.insertItem(876, "Charlie");

    // Imprime la tabla después de las inserciones
    cout << "Table after insertions:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;

    // Verifica si la tabla está vacía nuevamente
    if (ht.isEmpty()) {
        cout << "Incorrect Answer: Table is empty." << endl;
    } else {
        cout << "Correct Answer: Table is not empty." << endl;
    }

    // Elimina algunos elementos de la tabla
    ht.removeItem(201);
    ht.removeItem(422);

    // Imprime la tabla después de las eliminaciones
    cout << "Table after removals:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;

    // Inserta un elemento con una clave duplicada
    ht.insertItem(123, "Rodrigo");

    // Imprime la tabla después de insertar una clave duplicada
    cout << "Table after insertion of duplicate key:" << endl;
    ht.printTable();
    cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << endl;

    // Realiza algunas búsquedas en la tabla
    cout << "Search for key 201: " << ht.searchTable(201) << endl;
    cout << "Search for key 422: " << ht.searchTable(422) << endl;
    cout << "Search for key 123: " << ht.searchTable(123) << endl;

    return 0;
}
