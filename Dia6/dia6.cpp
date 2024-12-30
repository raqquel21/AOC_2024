#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <utility> // Para std::pair
using namespace std;

struct Point {
    Point(const int row = 0, const int col = 0) : row(row), col(col) {}
    int row;
    int col;
    bool operator==(const Point& p) const {
        return p.row == row && p.col == col;
    }
};

// Hasher para unordered_set
struct Hasher {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.row) ^ (hash<int>()(p.col) << 1);
    }
};

// Posibles movimientos
const vector<Point> moves{
    Point(1, 0),  // Abajo
    Point(0, -1), // Izquierda
    Point(-1, 0), // Arriba
    Point(0, 1),  // Derecha
};

// Verifica si un punto está dentro del mapa
const bool in_map(const Point& p, const vector<string>& map) {
    return !(p.col >= map[0].size() || p.col < 0 || p.row >= map.size() || p.row < 0);
}

// Enumerate manual: devuelve un vector de pares (índice, elemento)
template <typename T>
vector<pair<size_t, typename T::value_type>> enumerate(const T& container) {
    vector<pair<size_t, typename T::value_type>> result;
    size_t idx = 0;
    for (const auto& elem : container) {
        result.emplace_back(idx++, elem);
    }
    return result;
}

int main(int argc, char* argv[]) {
    string input = "input";
    if (argc > 1) {
        input = argv[1];
    }

    ifstream file(input);
    string line;
    vector<string> map;
    Point start;

    // Leer el mapa y encontrar la posición inicial
    while (getline(file, line)) {
        map.push_back(line);
        for (const auto& [idx, c] : enumerate(line)) {
            if (c == '^') {
                start.row = map.size() - 1;
                start.col = idx;
            }
        }
    }

    unordered_set<Point, Hasher> visited;
    auto current = start;
    visited.insert(current);
    int idx = 2;

    // Simulación del movimiento
    while (true) {
        const auto next = Point(current.row + moves[idx].row, current.col + moves[idx].col);
        if (!in_map(next, map)) break;
        if (map[next.row][next.col] != '#') {
            visited.insert(next);
            current = next;
        } else {
            idx += 1;
            idx %= 4;
        }
    }
int size=visited.size();
    // Resultado
    cout << size << '\n';
    return 0;
}
