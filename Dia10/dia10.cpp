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
    vector<vector<int>> vec;
    while (getline(file, line)) {
        vector<int> tmp;
        for (char c : line) {
            tmp.push_back(c - '0'); // Convertir char a int
        }
        vec.push_back(tmp);
    }

    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int fila = vec.size();
    int columna = vec[0].size();
    int totalScore = 0;

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            if (vec[i][j] == 0) { // Encontrar un punto de inicio
                unordered_set<int> visitado; // Para rastrear posiciones de altura 9 visitadas
                queue<pair<int, int>> cola;
                cola.push({i, j});
                int score = 0;

                while (!cola.empty()) {  // Mientras que la cola no esté vacía
                    auto curr_pos = cola.front();
                    cola.pop();
                    int curr_i = curr_pos.first;
                    int curr_j = curr_pos.second;

                    if (vec[curr_i][curr_j] == 9) {
                        // Si llegamos a una altura 9, contarla si no ha sido visitada
                        int pos_key = curr_i * columna + curr_j;
                        if (visitado.find(pos_key) == visitado.end()) {
                            score++;
                            visitado.insert(pos_key);
                        }
                    } else {
                        // Explorar vecinos
                        for (auto d : dirs) {
                            int new_i = curr_i + d.first;
                            int new_j = curr_j + d.second;
                            if (new_i >= 0 && new_i < fila && new_j >= 0 && new_j < columna &&
                                vec[new_i][new_j] == vec[curr_i][curr_i] + 1) {
                                cola.push({new_i, new_j});
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
