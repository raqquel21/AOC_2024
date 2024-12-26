#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Función para contar caminos distintos hacia la altura 9
int countPaths(int r, int c, const vector<vector<int>>& grid, unordered_map<string, int>& memo) {
    if (grid[r][c] == 9) {
        return 1; // Se ha llegado a una altura 9
    }

    string key = to_string(r) + "," + to_string(c);
    if (memo.find(key) != memo.end()) {
        return memo[key]; // Retornar resultado almacenado
    }

    int paths = 0;
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    // Explorar vecinos
    for (auto d : dirs) {
        int new_r = r + d.first;
        int new_c = c + d.second;
        if (new_r >= 0 && new_r < grid.size() && new_c >= 0 && new_c < grid[0].size() &&
            grid[new_r][new_c] == grid[r][c] + 1) {
            paths += countPaths(new_r, new_c, grid, memo);
        }
    }

    memo[key] = paths; // Almacenar resultado
    return paths;
}

int main() {
    ifstream file("input");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string line;
    vector<vector<int>> grid;
    while (getline(file, line)) {
        vector<int> tmp;
        for (char c : line) {
            tmp.push_back(c - '0'); // Convertir char a int
        }
        grid.push_back(tmp);
    }

    int totalRating = 0;

    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 0) { // Encontrar un trailhead
                unordered_map<string, int> memo; // Para almacenar resultados de caminos
                int rating = countPaths(r, c, grid, memo); // Contar caminos desde el trailhead
                totalRating += rating; // Sumar el rating de este trailhead
            }
        }
    }

    cout << totalRating << endl; // Imprimir el puntaje total
    file.close(); // Cerrar el archivo
    return 0;
}
