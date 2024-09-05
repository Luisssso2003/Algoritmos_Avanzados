#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Clase Node que representa cada estado del puzzle
class Node {
public:
    vector<vector<char>> data; // Matriz del estado del puzzle
    int level; // Nivel del nodo en el árbol
    int fval;  // Valor f del nodo (f(x) = h(x) + g(x))

    // Constructor del nodo
    Node(vector<vector<char>> data, int level, int fval) {
        this->data = data;
        this->level = level;
        this->fval = fval;
    }

    // Método para generar nodos hijos moviendo el espacio vacío en las 4 direcciones posibles
    vector<Node> generate_child() {
        int x, y;
        find(data, '_', x, y); // Encuentra la posición del espacio vacío
        vector<vector<int>> val_list = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}};
        vector<Node> children;

        for (auto i : val_list) {
            vector<vector<char>> child = shuffle(data, x, y, i[0], i[1]);
            if (!child.empty()) {
                Node child_node(child, level + 1, 0);
                children.push_back(child_node);
            }
        }
        return children;
    }

private:
    // Método para mover el espacio vacío y generar un nuevo estado del puzzle
    vector<vector<char>> shuffle(vector<vector<char>> puz, int x1, int y1, int x2, int y2) {
        if (x2 >= 0 && x2 < puz.size() && y2 >= 0 && y2 < puz[0].size()) {
            vector<vector<char>> temp_puz = copy(puz);
            swap(temp_puz[x2][y2], temp_puz[x1][y1]);
            return temp_puz;
        } else {
            return {};
        }
    }

    // Copiar la matriz para crear una nueva instancia
    vector<vector<char>> copy(vector<vector<char>> root) {
        vector<vector<char>> temp = root;
        return temp;
    }

    // Método para encontrar la posición del espacio vacío en el puzzle
    void find(vector<vector<char>> puz, char x, int &row, int &col) {
        for (int i = 0; i < puz.size(); i++) {
            for (int j = 0; j < puz[i].size(); j++) {
                if (puz[i][j] == x) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }
};

// Clase Puzzle que controla el funcionamiento del juego
class Puzzle {
public:
    int n = 3; // Tamaño del puzzle (3x3)
    vector<Node> open; // Lista de nodos abiertos (por explorar)
    vector<Node> closed; // Lista de nodos cerrados (ya explorados)

    // Función heurística para calcular el valor f(x) = h(x) + g(x)
    int f(Node start, vector<vector<char>> goal) {
        return h(start.data, goal) + start.level;
    }

    // Función heurística que calcula la cantidad de posiciones incorrectas
    int h(vector<vector<char>> start, vector<vector<char>> goal) {
        int temp = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (start[i][j] != goal[i][j] && start[i][j] != '_') {
                    temp++;
                }
            }
        }
        return temp;
    }

    // Proceso principal del algoritmo A*
    vector<vector<vector<char>>> process(vector<vector<char>>& start_data, vector<vector<char>>& goal_data) {
        Node start(start_data, 0, 0); // Nodo inicial
        start.fval = f(start, goal_data); // Calculamos el valor f del nodo inicial
        open.push_back(start); // Añadimos el nodo inicial a la lista de abiertos

        vector<vector<vector<char>>> steps;
        while (true) {
            Node cur = open.front(); // Tomamos el primer nodo de la lista de abiertos
            steps.push_back(cur.data);  // Guardamos el estado actual del puzzle

            if (h(cur.data, goal_data) == 0) {
                return steps;  // Devolvemos todos los pasos cuando se resuelve el puzzle
            }

            // Generamos los hijos del nodo actual
            vector<Node> children = cur.generate_child();
            for (auto child : children) {
                child.fval = f(child, goal_data);
                open.push_back(child);
            }

            closed.push_back(cur); // Movemos el nodo actual a la lista de cerrados
            open.erase(open.begin()); // Eliminamos el nodo actual de la lista de abiertos

            // Ordenamos la lista de abiertos según el valor f
            sort(open.begin(), open.end(), [](Node a, Node b) {
                return a.fval < b.fval;
            });
        }
    }
};

// Función para imprimir el estado del puzzle
void print_puzzle(const vector<vector<char>>& data) {
    for (const auto& row : data) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Definimos el estado inicial y el estado objetivo
    vector<vector<char>> start_state = {
        {'2', '8', '3'},
        {'1', '6', '4'},
        {'7', '_', '5'}
    };

    vector<vector<char>> goal_state = {
        {'1', '2', '3'},
        {'8', '_', '4'},
        {'7', '6', '5'}
    };

    Puzzle puzzle;
    vector<vector<vector<char>>> solution = puzzle.process(start_state, goal_state);

    cout << "Pasos para resolver el puzzle:" << endl;
    for (size_t i = 0; i < solution.size(); ++i) {
        cout << "Paso " << i << ":" << endl;
        print_puzzle(solution[i]);
    }

    cout << "¡Puzzle resuelto!" << endl;

    return 0;
}