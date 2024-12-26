#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

// MergeSort para ordenar los vectores
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Cálculo de las diferencias usando recursión
int calcDiff(const vector<int>& fila1, const vector<int>& fila2, int l, int r) {
    if (l == r) return abs(fila1[l] - fila2[l]);

    int mid = l + (r - l) / 2;
    int leftSum = calcDiff(fila1, fila2, l, mid);
    int rightSum = calcDiff(fila1, fila2, mid + 1, r);

    return leftSum + rightSum;
}

// Cálculo del producto usando recursión
int calcProduct(const vector<int>& fila1, const vector<int>& fila2, int l, int r) {
    if (l == r) return fila1[l] * count(fila2.begin(), fila2.end(), fila1[l]);

    int mid = l + (r - l) / 2;
    int leftProduct = calcProduct(fila1, fila2, l, mid);
    int rightProduct = calcProduct(fila1, fila2, mid + 1, r);

    return leftProduct + rightProduct;
}

int main() {
    string linea;
    int n = 1000;
    vector<int> fila1(n);
    vector<int> fila2(n);

    ifstream fich("input");
    if (!fich.is_open()) {
        cerr << "Error al abrir el fichero\n";
        exit(EXIT_FAILURE);
    }

    int pos = 0;
    while (getline(fich, linea)) {
        istringstream ss(linea);
        ss >> fila1[pos] >> fila2[pos];
        pos++;
    }

    // Ordenar usando MergeSort
    mergeSort(fila1, 0, n - 1);
    mergeSort(fila2, 0, n - 1);

    // Calcular la suma de diferencias
    int res = calcDiff(fila1, fila2, 0, n - 1);

    // Calcular el producto acumulativo
    int multipl = calcProduct(fila1, fila2, 0, n - 1);

    cout << multipl << endl;
    cout << res << endl;

    fich.close();
    return 0;
}

