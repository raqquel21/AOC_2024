#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Función para contar caminos distintos hacia la altura 9
int countPaths(int i, int j, const vector<vector<int>>& vec, unordered_map<string, int>& nodo) {
    if (vec[i][j] == 9) {
        return 1; // Se ha llegado a una altura 9
    }

    string key = to_string(i) + "," + to_string(j);
    if (nodo.find(key) != nodo.end()) {
        return nodo[key]; // Retornar resultado almacenado
    }

    int paths = 0;
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    // Explorar vecinos
    for (auto d : dirs) {
        int new_i = i + d.first;
        int new_c = j + d.second;
        if (new_i >= 0 && new_i < vec.size() && new_c >= 0 && new_c < vec[0].size() && vec[new_i][new_c] == vec[i][j] + 1) {
            paths += countPaths(new_i, new_c, vec, nodo);
        }
    }

    nodo[key] = paths; // Almacenar resultado
    return paths;
}

int main() {
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

    int totalRating = 0;

    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            if (vec[i][j] == 0) { // Encontrar un trailhead
                unordered_map<string, int> nodo; // Para almacenar resultados de caminos
                int rating = countPaths(i, j, vec, nodo); // Contar caminos desde el trailhead
                totalRating += rating; // Sumar el rating de este trailhead
            }
        }
    }

    cout << totalRating << endl; // Imprimir el puntaje total
    file.close(); // Cerrar el archivo
    return 0;
}
