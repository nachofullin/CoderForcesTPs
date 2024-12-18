#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long countA = 0, countB = 0;  //contar la cant de nodos de los conjuntos A y B
vector<int> conjuntos;        //trackear si un nodo pertenece a A o B (0 o 1)


void dfsRec(vector<vector<int>>& adyacencias, vector<bool> &visited, int s, int conj) {
    visited[s] = true;
    conjuntos[s] = conj;

    if(conj == 0) {
        countA++;
    } else {
        countB++;
    }

    for (int vecino : adyacencias[s]) {
        if (visited[vecino] == false) {
            dfsRec(adyacencias, visited, vecino, 1-conj);   //recursiva de dfs y le cambio el conjunto (si es 0 pasa a 1 y si es 1 pasa a 0)
        }
    }
}


void dfs(vector<vector<int>>& adyacencias) {
    vector<bool> visited(adyacencias.size(), false);    //vector para trackear visited
    dfsRec(adyacencias, visited, 1, 0);   
}   

int main() {
    int n;
    cin >> n;   //cant de nodos

    vector<vector<int>> adyacencias(n+1);
    conjuntos.resize(n+1);

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        adyacencias[u].push_back(v);
        adyacencias[v].push_back(u);
    }
    dfs(adyacencias);

    long long maximo = countA * countB - (n -1);      //calculo el maximo que va a ser la cant maxima de aristas menos las que ya existen
    cout << maximo << endl;

    return 0;
}