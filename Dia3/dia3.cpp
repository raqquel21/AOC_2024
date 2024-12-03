#include <climits>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <utility>
#include <vector>
#include <math.h>
#include <regex> // Necesario para buscar con patrones
using namespace std;

// Buscar cadena de caracteres mul(x, y) y calcular x*y
int multip_cadena(int x, int y) {
    return x * y;
}

int main() {
    int res = 0; // Acumula el resultado
    string contenido;
    bool enabled = true; // Por defecto, las multiplicaciones están habilitadas

    // Abrir archivo en modo lectura
    ifstream fich("input");
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    // Leer todo el contenido del archivo en un string
    stringstream buffer;
    buffer << fich.rdbuf(); 
    contenido = buffer.str(); 

    // Expresión regular para buscar patrones como mul(x, y), do(), y don't()
    regex pattern(R"(mul\((\d+),\s*(\d+)\)|do\(\)|don't\(\))");
    smatch matches;

    // Usar un iterador para encontrar todas las coincidencias
    auto it = contenido.cbegin();
    auto end = contenido.cend();
    while (regex_search(it, end, matches, pattern)) {
        // Si encontramos una instrucción do(), habilitamos las multiplicaciones
        if (matches[0] == "do()") {
            enabled = true;
        }
        // Si encontramos una instrucción don't(), deshabilitamos las multiplicaciones
        else if (matches[0] == "don't()") {
            enabled = false;
        }
        // Si encontramos una instrucción mul(x, y)
        else if (matches[0].str().find("mul(") != string::npos && enabled) {
            // Extraer x e y de las coincidencias
            int x = stoi(matches[1]);
            int y = stoi(matches[2]);

            // Calcular el producto y sumarlo a res
            res += multip_cadena(x, y);
        }

        // Mover el iterador al final de la coincidencia actual
        it = matches.suffix().first;
    }

    // Imprimir el resultado
    cout << "Resultado: " << res << endl;

    // Cerrar el archivo (buena práctica)
    fich.close();
    return 0;
}
