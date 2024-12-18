#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring> // Para memset

using namespace std;

int res_parciales[200][201][201];   //memo
vector<int> seq;
int n;

int borw(int i, int ultimo_blanco, int ultimo_negro) {
    int res;

    if (i == n) {
        return 0; //sumo 0 a res porque termine
    }

    if (res_parciales[i][ultimo_blanco + 1][ultimo_negro + 1] != -1) {
        return res_parciales[i][ultimo_blanco + 1][ultimo_negro + 1];
    }

    // opcion no pinto
    res = 1 + borw(i + 1, ultimo_blanco, ultimo_negro);
    
    //opcion pinto blanco
    if (ultimo_blanco == -1 || seq[i] < seq[ultimo_blanco]) {
        res = min(res, borw(i + 1, i, ultimo_negro));
    }

    //opcion pinto negro
    if (ultimo_negro == -1 || seq[i] > seq[ultimo_negro]) {
        res = min(res, borw(i + 1, ultimo_blanco, i));
    }  

    res_parciales[i][ultimo_blanco + 1][ultimo_negro + 1] = res;
    return res;
}

int main() {
    while (1) {
        cin >> n;
        if (n == -1) {
            break;
        }
        seq = vector<int>(n);
        for (int i = 0; i < n; i ++) {
            cin >> seq[i];
        }
        memset(res_parciales, -1, sizeof(res_parciales)); //inicializo la matriz con todo -1
        cout << borw(0, -1, -1) << endl;
    }

    return 0;
}