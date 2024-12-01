/***********************************************************************/
/* 		Dia 1 : Ana Asenjo y Raquel Montoliu                   */
/***********************************************************************/
/* Tenemos que leer la lista de la izquierda y la de la derecha y      */
/* desde los números más pequeños hasta los más grandes de cada una    */
/* calcular su diferencia y sumar el total                             */
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

// Ordenamos los dos vectores (filas) antes de calcular la distancia
void BubbleSort(vector<int>& v){
	int n = v.size();
	
	for (int i = 0; i <= n -1; i++){
		for (int j = 1; j <= n-1; j++){
			if(v[j] > v[i]){ // De menor a mayor
				swap(v[j], v[i]);
			}
		}
	}
}

int main(){
	string linea;
	int n = 1000;  // Hay 1000 filas (wc input)
	vector<int> fila1(n);
	vector<int> fila2(n);

	int pos = 0; // Lo usamos para saber en que posicion nos encontramos dentro del vector
	int min_value1 = INT_MAX; // Está en la libreria de <climits>
	int min_value2 = INT_MAX;
	int diff = 0;
	int res = 0;
	
	// Abrir el fichero input
	ifstream fich("input");
	if(!fich.is_open()){
		cout << "Error al abrir el fichero\n";
		exit(EXIT_FAILURE);
	}
	
	// Leemos las lineas
	while(getline(fich, linea)){
		istringstream ss(linea);
		ss >> fila1[pos] >> fila2[pos];
		pos++;
	}

	BubbleSort(fila1);
	BubbleSort(fila2);
	// Imprimir fila 1
	//for(int i = 0; i < n; i++){
	//	cout << fila1[i] << endl;
	//}
	for (int i = 0; i < n; i++){
		diff = abs(fila1[i] - fila2[i]);
		res+=diff;
	}
	int multipl = 0;
	for (int i = 0; i < n; i++){
		int sum = 0;
		for(int j = 0; j < n; j++){
			if (fila1[i] == fila2[j]){
				sum++;
			}
		}
		multipl += sum*fila1[i];
	}
	cout << multipl << endl;
	cout << res << endl;
	
	fich.close();
	return 0;
}
