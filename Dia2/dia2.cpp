/***********************************************************************/
/* 		Dia 2 : Ana Asenjo y Raquel Montoliu                   */
/***********************************************************************/
/* Calcular la distancia numérica de cada fila y comprobar si es < 3   */
/***********************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;


// Parte 1
bool Safe(vector<int>& report) {
    int n = report.size();

    bool creciente = true;
    bool decreciente = true;

    for (int i = 0; i < n - 1; i++) {
        int diff = abs(report[i] - report[i + 1]);
        if(diff > 3 || diff <= 0) { 
            return false;
        }
        if(report [i] < report [i + 1]) { decreciente = false;}
        if(report [i] > report [i + 1]) { creciente = false;}

    }
    // Devuelve true o false si la salida es creciente o decreciente con
    // la condición de seguridad
    return creciente || decreciente;
}
// Parte 2
bool puedeConvertirseSafe (vector<int>& report){
    int n = report.size();
    for (int i = 0; i < n; i++){
        vector<int> Nvector = report;
        if(Safe(Nvector) == false) {
            // Solo hay que borrar el nivel de la posicion i
            Nvector.erase(Nvector.begin() + i);
        }
        // Volvemos a comprobarlo:
        if(Safe(Nvector) == true){ return true; }

    }
    return false;
}

int main() {
    ifstream fich("input"); // Archivo de entrada
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> report; // Almacena los datos del archivo
    string linea;
    int safe = 0;

    // Leer archivo línea por línea
    while (getline(fich, linea)) {
        istringstream ss(linea);
        vector<int> fila; // Almacena una fila del archivo
        int valor;

        // Leer valores de la línea
        while (ss >> valor) {
            fila.push_back(valor);
        }
        report.push_back(fila); // Añadir la fila al reporte
    }
    for (int i = 0; i < report.size(); i++){
        if(Safe(report[i]) == true || puedeConvertirseSafe(report[i])){safe++;} 
    }

    cout << "Safe: " << safe << endl;
    fich.close();
    return 0;
}

