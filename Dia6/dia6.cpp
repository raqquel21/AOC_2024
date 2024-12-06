/***********************************************************************/
/* 		Dia 1 : Ana Asenjo, Raquel Montoliu y Siya Wu                   */
/***********************************************************************/
/* Tenemos que recorrer un mapa para saber cuantas posiciones nuevas   */
/* descubre el guardia, siguiendo las reglas de movimiento descritas   */
/***********************************************************************/

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
using namespace std;

struct guardia{
    int x;
    int y;
    int distancia=0;
};
enum direcciones {ARRIBA, ABAJO, IZQUIERDA, DERECHA}; // Como si fuera un diccionario
bool fueralimit(vector<string> mapa, int x, int y){
    if (x < 0 || y < 0 || x >= mapa.size() || y >= mapa[0].size()){
        return true;
    }
    return false;
}
direcciones turnRight(direcciones dir) {
    return static_cast<direcciones>((dir + 1) % 4);
}

void localizacion(vector<string> mapa,guardia &g,direcciones dir){
    for (int i = 0; i < mapa.size(); ++i){
        for (int j = 0; j < mapa[0].size(); ++j){
            if (mapa[i][j] == '^') { g = {i, j}; dir = ARRIBA; }
            else if (mapa[i][j] == '>') { g = {i, j}; dir = DERECHA; }
            else if (mapa[i][j] == 'v') { g = {i, j}; dir =ABAJO; }
            else if (mapa[i][j] == '<') { g = {i, j}; dir = IZQUIERDA; }
        }
    }
}
bool obstaculo(vector<string> mapa, int x, int y){
    if(mapa[x][y]=='#'){
        return true;
    }
    return false;
}
guardia movimiento(guardia g, direcciones dir){
    if(dir==ARRIBA){
        g.x--;
    }
    else if(dir==ABAJO){
        g.x++;
    }
    else if(dir==IZQUIERDA){
        g.y--;
    }
    else if(dir==DERECHA){
        g.y++;
    }
return g;
}
int main(){
    vector<string> mapa;
    ifstream fich("input");
    if (!fich.is_open()) {
        cout << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(fich, line)) {
        mapa.push_back(line);
    }
    guardia g;
    direcciones dir;
    localizacion(mapa,g,dir);

    while(!fueralimit(mapa,g.x,g.y)){
        int x=g.x;
        int y=g.y;
        g=movimiento(g,dir);
        if(obstaculo(mapa,g.x,g.y)){
            dir=turnRight(dir);
            g.x=x;
            g.y=y;
        }
        if(mapa[g.x][g.y]=='.'){
            mapa[g.x][g.y]='X';
            g.distancia++;
        }
    }
    cout<<g.distancia<<endl;
    fich.close();
    return 0;
}
