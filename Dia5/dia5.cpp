#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Función para dividir una regla "X|Y" en dos números
pair<int, int> ParesNum(const string& linea) {
    stringstream ss(linea);
    int x, y;
    char sep;
    ss >> x >> sep >> y; // Leer "X|Y"
    return {x, y};
}

// Función para dividir una línea "A,B,C" en un vector de números
vector<int> DivLinea(const string& linea) {
    stringstream ss(linea);
    vector<int> vec;
    string num;
    while (getline(ss, num, ',')) { // Leer números separados por comas
        vec.push_back(stoi(num));
    }
    return vec;
}

// Función para verificar si una actualización cumple las reglas
bool VecValido(const vector<int>& vec, const vector<pair<int, int>>& reglas) {
    // Mapear las posiciones de cada página en la actualización
    vector<int> pos(101, -1); // Suponiendo que los números de páginas son <= 100
    for (size_t i = 0; i < vec.size(); ++i) {
        pos[vec[i]] = i;
    }

    // Verificar cada regla
    for (const auto& rule : reglas) {
        int x = rule.first;
        int y = rule.second;

        // Si ambos números están en la actualización, verificar su orden
        if (pos[x] != -1 && pos[y] != -1 && pos[x] > pos[y]) {
            return false; // Orden incorrecto
        }
    }
    return true;
}

// Función para ordenar una actualización incorrecta según las reglas
vector<int> sortvec(const vector<int>& vec, const vector<pair<int, int>>& reglas) {
    vector<int> ordenarVec = vec;

    // Intentamos ordenar usando las reglas de precedencia
    bool swapped;
    do {
        swapped = false;
        // Comparamos todas las reglas 
        for (const auto& rule : reglas) {
            int x = rule.first;
            int y = rule.second;

            // Si x está después de y en la actualización, los intercambiamos
            auto itX = find(ordenarVec.begin(), ordenarVec.end(), x);
            auto itY = find(ordenarVec.begin(), ordenarVec.end(), y);
            if (itX != ordenarVec.end() && itY != ordenarVec.end() && itX > itY) {
                swap(*itX, *itY);
                swapped = true;
            }
        }
    } while (swapped); // Continuamos hasta que no haya más intercambios

    return ordenarVec;
}

int main() {
    // Abrir el archivo
    ifstream file("input");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<pair<int, int>> reglas; // Lista de reglas como pares (X, Y)
    vector<vector<int>> vecs; // Lista de actualizaciones
    string linea;
    bool readingreglas = true;

    while (getline(file, linea)) {

        if (readingreglas) {
            // Leer reglas hasta encontrar una línea sin "|"
            if (linea.find('|') != string::npos) {
                reglas.push_back(ParesNum(linea)); // Guardar la regla
            } else {
                readingreglas = false; // Cambiar a modo de lectura de actualizaciones
            }
        }

        if (!readingreglas) {
            // Leer y guardar actualizaciones
            vecs.push_back(DivLinea(linea));
        }
    }

    file.close();

    // Verificar y ordenar actualizaciones incorrectas
    int sum = 0;

    for (const auto& vec : vecs) {
        if (!VecValido(vec, reglas)) {
            // Ordenar la actualización incorrecta
            vector<int> ordenarVec = sortvec(vec, reglas);
            // Encontrar el número central
            int middleIndex = ordenarVec.size() / 2;
            sum += ordenarVec[middleIndex];
        }
    }

    cout << "Resultado: " << sum << endl;

    return 0;
}

