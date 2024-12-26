#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Mapa para almacenar las piedras y sus cantidades
static unordered_map<string, uint64_t> piedras;

// Función para dividir una cadena por un delimitador y devolver los elementos como un vector
static vector<string> Split(const string& s, const string& delimit) {
    vector<string> result;
    size_t start = 0, end = 0;
    while ((end = s.find(delimit, start)) != string::npos) {
        result.push_back(s.substr(start, end - start)); // Extrae la parte antes del delimitador
        start = end + delimit.length(); // Mueve el inicio después del delimitador
    }
    result.push_back(s.substr(start)); // Añade la última parte que no tiene delimitador
    return result;
}

// Función para insertar o actualizar la cantidad de una piedra en el mapa
static inline void Insert(const string& key, uint64_t count) {
    piedras[key] += count;
}

// Función para generar la siguiente generación de piedras
static void NextGen() {
    unordered_map<string, uint64_t> prev = piedras; // Guardamos el estado anterior de las piedras
    piedras.clear(); // Limpiamos el mapa para llenarlo con la nueva generación

    // Procesamos cada piedra
    for (const auto& piedra : prev) {
        const auto& [id, count] = piedra;

        if (id == "0") {
            // Regla 1: Si la piedra es 0, la cambiamos por 1
            Insert("1", count);
        } else {
            int sz = id.size();
            if (sz % 2 == 0) {
                // Regla 2: Si el número tiene un número par de dígitos, lo dividimos
                string left = to_string(stoll(id.substr(0, sz / 2)));  // Mitad izquierda
                string right = to_string(stoll(id.substr(sz / 2)));   // Mitad derecha
                Insert(left, count);  // Insertamos la parte izquierda
                Insert(right, count); // Insertamos la parte derecha
            } else {
                // Regla 3: Si el número tiene un número impar de dígitos, lo multiplicamos por 2024
                Insert(to_string(2024 * stoll(id)), count);
            }
        }
    }
}

// Función para calcular el total de piedras después de un número de parpadeos
static uint64_t CalculateTotal(int start, int blinks) {
    // Generamos las siguientes generaciones de piedras
    for (int i = start; i < blinks; ++i) {
        NextGen();
    }

    uint64_t total = 0;
    // Sumar todas las cantidades de piedras
    for (const auto& piedra : piedras) {
        total += piedra.second;
    }
    return total;
}

int main() {
    ifstream file("input"); // Abrir el archivo de entrada
    string line;
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Leer las piedras desde el archivo
    while (getline(file, line)) {
        vector<string> nums = Split(line, " ");  // Dividir la línea en números
        for (const auto& n : nums) {
            Insert(n, 1); // Insertar cada piedra con un conteo inicial de 1
        }
    }

    // Mostrar los resultados para las dos partes del problema
    cout << "Día 11: Piedras Plutonianas" << endl;
    cout << "Parte 1   - " << CalculateTotal(0, 25) << endl;
    cout << "Parte 2   - " << CalculateTotal(25, 75) << endl;
    
    file.close();
    return 0;
}

