#include <climits>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#define ANCHO 101
#define ALTO 103

using namespace std;

class Robot {
public:
    int posx;
    int posy;
    int dx;
    int dy;
};

class Celda {
public:
    int rob = 0;
};

// Mueve el robot según su velocidad durante t segundos
void movrobot(Robot &r, int t) {
    r.posx = r.posx + r.dx * t;
    r.posy = r.posy + r.dy * t;
    
    // Implementar el wrapping alrededor de los bordes
    r.posx = (r.posx + ANCHO) % ANCHO;
    r.posy = (r.posy + ALTO) % ALTO;
}

// Calcula cuántos robots hay en cada celda
void robots_en_celda(Celda c[ANCHO][ALTO], vector<Robot> &robots) {
    for (int i = 0; i < robots.size(); i++) {
        int x = robots[i].posx;
        int y = robots[i].posy;
        c[x][y].rob += 1;
    }
}

// Calcula el total de robots en los cuadrantes
int total(Celda c[ANCHO][ALTO]) {
    int res = 1;
    bool hayrobot = false;//en el hipotetico caso de que no haya robots

    // Recorremos las cuatro secciones del espacio (cuadrantes)
    for (int i = 0; i < (ANCHO-1) / 2; i++) {
        for (int j = 0; j < (ALTO-1) / 2; j++) {
            if (c[i][j].rob >= 1) {
                res *= c[i][j].rob;
                hayrobot = true;
            }
        }
    }

    for (int i = 0; i < (ANCHO-1) / 2; i++) {
        for (int j = (ALTO+1) / 2; j < ALTO; j++) {
            if (c[i][j].rob >= 1) {
                res *= c[i][j].rob;
                hayrobot = true;
            }
        }
    }

    for (int i = (ANCHO+1) / 2; i < ANCHO; i++) {
        for (int j = 0; j < (ALTO-1) / 2; j++) {
            if (c[i][j].rob >= 1) {
                res *= c[i][j].rob;
                hayrobot = true;
            }
        }
    }

    for (int i = (ANCHO+1) / 2; i < ANCHO; i++) {
        for (int j = (ALTO+1) / 2; j < ALTO; j++) {
            if (c[i][j].rob >= 1) {
                res *= c[i][j].rob;
                hayrobot = true;
            }
        }
    }

    if (hayrobot) {
        return res;
    } else {
        return 0;
    }
}

int main() {
    string linea;
    vector<string> posiciones;
    vector<string> direcciones;

    // Abrir el fichero input
    ifstream fich("input.txt");
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    // Leer las líneas del archivo y extraer posiciones y velocidades
    while (getline(fich, linea)) {
        istringstream ss(linea);
        string posic, direc;
        ss >> posic >> direc;
        posic = posic.substr(2);  // Eliminar "p="
        direc = direc.substr(2);  // Eliminar "v="
        posiciones.push_back(posic);
        direcciones.push_back(direc);
    }

    // Definir los robots basados en las posiciones y direcciones extraídas
    vector<Robot> robots;
    for (int i = 0; i < posiciones.size(); i++) {
        Robot r;
        r.posx = stoi(posiciones[i].substr(0, posiciones[i].find(",")));
        r.posy = stoi(posiciones[i].substr(posiciones[i].find(",") + 1));
        r.dx = stoi(direcciones[i].substr(0, direcciones[i].find(",")));
        r.dy = stoi(direcciones[i].substr(direcciones[i].find(",") + 1));
        robots.push_back(r);
    }

    // Crear la matriz de celdas
    Celda c[ANCHO][ALTO] = {};

    // Mover los robots y actualizar las celdas
    for (int i = 0; i < robots.size(); i++) {
        movrobot(robots[i], 100);
    }

    robots_en_celda(c, robots);

    // Calcular el total de robots en los cuadrantes.
    int resultado = total(c);
    cout << "El resultado final es: " << resultado << endl;

    fich.close();
    return 0;
}
