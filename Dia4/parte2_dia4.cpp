#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // Para reverse
using namespace std;

// Función para verificar si una celda puede ser el centro de un "X-MAS"
bool checkXMAS(const vector<string>& grid, int x, int y) {
    // Dimensiones de la sopa de letras
    int n = grid.size();
    int m = grid[0].size();

    // Coordenadas relativas de los caracteres en el patrón
    vector<pair<int, int>> positions = {
        {-1, -1}, {-1, 1},  // M.S (parte superior)
        {0, 0},             // A   (centro)
        {1, -1}, {1, 1}     // M.S (parte inferior)
    };

    // Las letras esperadas en cada posición del patrón
    string expected = "MASMAS";

    // Probar las dos orientaciones del patrón
    for (int orientation = 0; orientation < 2; ++orientation) {
        bool valid = true;
        for (int i = 0; i < positions.size(); ++i) {
            int nx = x + positions[i].first;
            int ny = y + positions[i].second;

            // Verificar límites y caracteres
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != expected[i]) {
                valid = false;
                break;
            }
        }
        if (valid) return true;

        // Cambiar orientación invirtiendo "MASMAS"
        reverse(expected.begin(), expected.end());
    }

    return false;
}

// Función para contar todas las configuraciones "X-MAS" en la sopa de letras
int countXMAS(const vector<string>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int count = 0;

    // Iterar sobre cada celda como posible centro del patrón
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (grid[x][y] == 'A' && checkXMAS(grid, x, y)) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    vector<string> sopa;
    ifstream fich("input"); // Archivo de entrada con la sopa de letras
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    // Leer la sopa de letras del archivo
    string line;
    while (getline(fich, line)) {
        sopa.push_back(line);
    }
    fich.close();

    // Contar y mostrar el resultado
    int result = countXMAS(sopa);
    cout << "El patrón X-MAS aparece " << result << " veces en la sopa de letras." << endl;

    return 0;
}

