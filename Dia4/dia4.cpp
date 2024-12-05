/*******************************************/
/*  Ana Asenjo, Raquel Montoliu y Siya Wu  */
/*******************************************/
/*                 Dia 4                   */
/*    Encontrar los carácteres X-MAS       */
/*******************************************/


#include <climits>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <utility>
#include <vector>
#include <math.h>
using namespace std;

// Direcciones de búsqueda: {dx, dy} (fila, columna)
const vector<pair<int, int>> directions = {
    {0, 1},   // Derecha
    {1, 0},   // Abajo
    {1, 1},   // Diagonal hacia abajo derecha
    {1, -1},  // Diagonal hacia abajo izquierda
    {0, -1},  // Izquierda
    {-1, 0},  // Arriba
    {-1, -1}, // Diagonal hacia arriba izquierda
    {-1, 1}   // Diagonal hacia arriba derecha
};

// Función para verificar si "XMAS" se encuentra desde (x, y) en una dirección específica
bool checkWord(const vector<string>& grid, int x, int y, int dx, int dy) {
    string word = "XMAS";
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < word.size(); ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != word[i]) {
            return false;
        }
    }
    return true;
}

// Función para contar todas las apariciones de "XMAS" en la sopa de letras
int countXMAS(const vector<string>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int count = 0;

    // Iterar por cada celda de la matriz
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            // Verificar en cada dirección
            for (const auto& dir : directions) {
                int dx = dir.first;
                int dy = dir.second;
                if (checkWord(grid, x, y, dx, dy)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

int main() {
    vector<string> sopa;
    ifstream fich("input");
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }
    string line;
    while(getline(fich, line)){
        sopa.push_back(line);
    }

  
    
    // Contar y mostrar el resultado
    int result = countXMAS(sopa);
    cout << "La palabra XMAS aparece " << result << " veces en la sopa de letras." << endl;
    fich.close();
    return 0;
}
