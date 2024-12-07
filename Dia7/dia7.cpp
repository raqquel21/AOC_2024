#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


// He tenido que usar stoll y int64_t porque si no está fuera de rango


// Leer una línea y convertirla en un vector de enteros
vector<int> LeerLinea(const string& linea) {
    stringstream ss(linea);
    vector<int> vec;
    string num;

    while (getline(ss, num, ' ')) { 
        if (!num.empty()) { 
            vec.push_back(stoi(num)); 
        }
    }

    return vec;
}

// Intentar todas las combinaciones de suma y multiplicación
bool ProbarOperaciones(const vector<int>& numeros, int64_t objetivo) {
    size_t n = numeros.size();
    size_t combinacionesTotales = 1 << (n - 1); // 2^(n-1) combinaciones (+ y *)

    // Probar todas las combinaciones posibles de operadores
    for (size_t mask = 0; mask < combinacionesTotales; ++mask) {
        int64_t resultado = numeros[0];
        for (size_t i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) { // Si el bit i está activo, usamos suma
                resultado += numeros[i + 1];
            } else { // Si el bit i no está activo, usamos multiplicación
                resultado *= numeros[i + 1];
            }
        }
        if (resultado == objetivo) {
            return true; // Encontramos una combinación válida
        }
    }
    return false; // No se encontró ninguna combinación
}

void procesarLinea(const string& linea, vector<int64_t>& resultados) {
    size_t pos = linea.find(':');
    if (pos == string::npos) {
        cerr << "Formato inválido: " << linea << endl;
        return;
    }

    int64_t objetivo = stoll(linea.substr(0, pos)); // Obtener el valor objetivo
    string numeros_str = linea.substr(pos + 1); // Obtener los números a la derecha de los ':'

    // Convertir los números a un vector
    vector<int> numeros = LeerLinea(numeros_str);



    // Probar si alguna combinación alcanza el objetivo
    if (ProbarOperaciones(numeros, objetivo)) {
        resultados.push_back(objetivo); // Si es válido, agregar el objetivo a los resultados
    }
}

int main() {
    ifstream fich("input");
    if (!fich.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    vector<int64_t> res;
    string linea;

    while (getline(fich, linea)) {
        procesarLinea(linea, res); // Procesar cada línea
    }
    fich.close();

    int64_t suma_resultados = 0;
    for (int64_t valor : res) {
        suma_resultados += valor; // Sumar los resultados
    }

    cout << "Resultado total de calibración: " << suma_resultados << endl;
    return 0;
}

