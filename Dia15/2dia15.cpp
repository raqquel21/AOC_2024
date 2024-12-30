#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <utility> // Para std::pair
using namespace std;

// Estructura Point con constructor
struct Point {
    int row;
    int col;

    // Constructor que acepta dos parámetros
    Point(int r = 0, int c = 0) : row(r), col(c) {}

    bool operator==(const Point& p) const {
        return row == p.row && col == p.col;
    }
    
    bool operator<(const Point& p) const {
        return row < p.row || (row == p.row && col < p.col);
    }
};

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

bool in_map(const Point& p, const vector<string>& map) {
    return p.row >= 0 && p.row < map.size() && p.col >= 0 && p.col < map[0].size();
}

bool move_obstacles(const Point& start, const Point& possible_move, vector<string>& map) {
    auto current = start;
    while (map[current.row][current.col] == 'O') {
        current.row += possible_move.row;
        current.col += possible_move.col;
    }
    if (map[current.row][current.col] == '.') {
        swap(map[current.row][current.col], map[start.row][start.col]);
        return true;
    }
    return false;
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

    while (getline(file, line) && !line.empty()) {
        map.push_back(line);
        for (const auto& [idx, ele] : enumerate(line)) {
            if (ele == '@') {
                start.row = map.size() - 1;
                start.col = idx;
            }
        }
    }

    string moves;
    while (getline(file, line)) {
        moves += line;
    }

    Point current = start;
    array<Point, 4> possible_moves {{
        Point(-1, 0),
        Point(0, 1),
        Point(1, 0),
        Point(0, -1)
    }};

    for (const auto move : moves) {
        int move_idx = 0;
        if (move == '^') {
            move_idx = 0;
        } else if (move == '>') {
            move_idx = 1;
        } else if (move == 'v') {
            move_idx = 2;
        } else if (move == '<') {
            move_idx = 3;
        }
        Point new_point(current.row + possible_moves[move_idx].row, current.col + possible_moves[move_idx].col);
        if (!in_map(new_point, map)) {
            continue;
        }
        if (map[new_point.row][new_point.col] == '#') {
            continue;
        }
        if (map[new_point.row][new_point.col] == 'O') {
            if (move_obstacles(new_point, possible_moves[move_idx], map)) {
                swap(map[new_point.row][new_point.col], map[current.row][current.col]);
                current = new_point;
            }
        }
        if (map[new_point.row][new_point.col] == '.') {
            swap(map[new_point.row][new_point.col], map[current.row][current.col]);
            current = new_point;
        }
    }

    int total = 0;
    for (const auto& [row_idx, row] : enumerate(map)) {
        for (const auto& [col_idx, ele] : enumerate(row)) {
            if (ele == 'O') total += (100 * row_idx + col_idx);
        }
    }
    cout << total << '\n';
    return 0;
}
