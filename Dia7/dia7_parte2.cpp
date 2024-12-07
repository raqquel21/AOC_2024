#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Leer una línea y convertirla en un vector de enteros
vector<int> LeerLinea(const string& linea) {
    vector<int> vec;
    stringstream ss(linea);
    string num;

    while (getline(ss, num, ' ')) { // Dividir por espacios
        if (!num.empty()) { // Ignorar cadenas vacías
            try {
                vec.push_back(stoi(num));
            } catch (const invalid_argument&) {
                cerr << "Error: No se pudo convertir \"" << num << "\" a entero." << endl;
            } catch (const out_of_range&) {
                cerr << "Error: Número fuera de rango \"" << num << "\"." << endl;
            }
        }
    }

    return vec;
}

// Calcular la concatenación de dos números
int64_t concatenar(int64_t a, int64_t b) {
    int64_t b_digits = b == 0 ? 1 : log10(b) + 1; // Cantidad de dígitos de b
    return a * pow(10, b_digits) + b; // Concatenar los dígitos de b a a
}

// Intentar todas las combinaciones de suma, multiplicación y concatenación
bool ProbarOperaciones(const vector<int>& numeros, int64_t objetivo) {
    size_t n = numeros.size();
    size_t combinacionesTotales = pow(3, n - 1); // 3^(n-1) combinaciones (+, *, ||)

    for (size_t mask = 0; mask < combinacionesTotales; ++mask) {
        int64_t resultado = numeros[0];
        size_t current_mask = mask;

        for (size_t i = 0; i < n - 1; ++i) {
            int op = current_mask % 3; // Operador actual (0: +, 1: *, 2: ||)
            current_mask /= 3;

            if (op == 0) { // Suma
                resultado += numeros[i + 1];
            } else if (op == 1) { // Multiplicación
                resultado *= numeros[i + 1];
            } else if (op == 2) { // Concatenación
                resultado = concatenar(resultado, numeros[i + 1]);
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

    int64_t objetivo;
    try {
        objetivo = stoll(linea.substr(0, pos));
    } catch (const invalid_argument&) {
        cerr << "Error: No se pudo convertir el objetivo en la línea \"" << linea << "\"." << endl;
        return;
    }

    string numeros_str = linea.substr(pos + 1);

    // Convertir los números a un vector
    vector<int> numeros = LeerLinea(numeros_str);

    if (numeros.empty()) {
        cerr << "Error: No se encontraron números válidos en la línea \"" << linea << "\"." << endl;
        return;
    }

    // Probar si alguna combinación alcanza el objetivo
    if (ProbarOperaciones(numeros, objetivo)) {
        resultados.push_back(objetivo);
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
        procesarLinea(linea, res);
    }
    fich.close();

    int64_t suma_resultados = 0;
    for (int64_t valor : res) {
        suma_resultados += valor;
    }

    cout << "Resultado total de calibración: " << suma_resultados << endl;
    return 0;
}

