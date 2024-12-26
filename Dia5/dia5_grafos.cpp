/*  Usamos el método con grafos  */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Función para dividir una línea separada por comas en un vector de enteros
vector<int> dividirPorComas(const string& linea) {
    vector<int> resultado;
    stringstream ss(linea);
    string elemento;
    while (getline(ss, elemento, ',')) {
        resultado.push_back(stoi(elemento));
    }
    return resultado;
}

// Función para construir un grafo a partir de las reglas
void construirGrafo(const vector<pair<int, int>>& reglas, unordered_map<int, vector<int>>& grafo) {
    for (const auto& regla : reglas) {
        int origen = regla.first;
        int destino = regla.second;
        grafo[origen].push_back(destino);
    }
}

// Función para verificar si una lista cumple las reglas de precedencia
bool listaValida(const vector<int>& lista, const unordered_map<int, vector<int>>& grafo) {
    unordered_map<int, int> posicion;
    for (size_t i = 0; i < lista.size(); ++i) {
        posicion[lista[i]] = i;
    }

    for (const auto& [origen, destinos] : grafo) {
        if (posicion.find(origen) != posicion.end()) {
            for (int destino : destinos) {
                if (posicion.find(destino) != posicion.end() && posicion[origen] > posicion[destino]) {
                    return false; // La regla no se cumple
                }
            }
        }
    }
    return true;
}

// Función para ordenar una lista según las reglas del grafo
vector<int> ordenarLista(const vector<int>& lista, const unordered_map<int, vector<int>>& grafo) {
    vector<int> resultado = lista;
    bool cambiado;

    do {
        cambiado = false;
        for (const auto& [origen, destinos] : grafo) {
            auto itOrigen = find(resultado.begin(), resultado.end(), origen);
            for (int destino : destinos) {
                auto itDestino = find(resultado.begin(), resultado.end(), destino);

                if (itOrigen != resultado.end() && itDestino != resultado.end() && itOrigen > itDestino) {
                    swap(*itOrigen, *itDestino);
                    cambiado = true;
                }
            }
        }
    } while (cambiado);

    return resultado;
}

// Función principal
int main() {
    ifstream archivo("input");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<pair<int, int>> reglas;
    vector<vector<int>> actualizaciones;
    string linea;
    bool leyendoActualizaciones = false;

    while (getline(archivo, linea)) {
        if (linea.empty()) {
            leyendoActualizaciones = true;
            continue;
        }

        if (!leyendoActualizaciones) {
            int x = stoi(linea.substr(0, 2));
            int y = stoi(linea.substr(3, 2));
            reglas.emplace_back(x, y);
        } else {
            actualizaciones.push_back(dividirPorComas(linea));
        }
    }
    archivo.close();

    // Construir el grafo a partir de las reglas
    unordered_map<int, vector<int>> grafo;
    construirGrafo(reglas, grafo);

    // Verificar y procesar las actualizaciones
    int suma = 0;

    for (const auto& lista : actualizaciones) {
        if (!listaValida(lista, grafo)) {
            vector<int> listaOrdenada = ordenarLista(lista, grafo);
            suma += listaOrdenada[listaOrdenada.size() / 2];
        }
    }

    // Imprimir el resultado
    cout << "Resultado: " << suma << endl;

    return 0;
}

