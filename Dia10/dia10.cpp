#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

int main() {
    // Abrir el archivo
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

    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int fila = grid.size();
    int columna = grid[0].size();
    int totalScore = 0;

    for (int r = 0; r < fila; ++r) {
        for (int c = 0; c < columna; ++c) {
            if (grid[r][c] == 0) { // Encontrar un punto de inicio
                unordered_set<int> visited; // Para rastrear posiciones de altura 9 visitadas
                queue<pair<int, int>> q;
                q.push({r, c});
                int score = 0;

                while (!q.empty()) {
                    auto curr_pos = q.front();
                    q.pop();
                    int curr_r = curr_pos.first;
                    int curr_c = curr_pos.second;

                    if (grid[curr_r][curr_c] == 9) {
                        // Si llegamos a una altura 9, contarla si no ha sido visitada
                        int pos_key = curr_r * columna + curr_c;
                        if (visited.find(pos_key) == visited.end()) {
                            score++;
                            visited.insert(pos_key);
                        }
                    } else {
                        // Explorar vecinos
                        for (auto d : dirs) {
                            int new_r = curr_r + d.first;
                            int new_c = curr_c + d.second;
                            if (new_r >= 0 && new_r < fila && new_c >= 0 && new_c < columna &&
                                grid[new_r][new_c] == grid[curr_r][curr_c] + 1) {
                                q.push({new_r, new_c});
                            }
                        }
                    }
                }
                totalScore += score; // Sumar el puntaje de este punto de inicio
            }
        }
    }

    cout << totalScore << endl; // Imprimir el puntaje total
    file.close(); 
    return 0;
}
