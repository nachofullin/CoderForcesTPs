#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> ady;
vector<int> estado, padre, discovery, low;
vector<pair<int, int>> puentes;
int tiempo;

void dfs(int v) {
    estado[v] = 1; // EMPECE_A_VER
    discovery[v] = low[v] = ++tiempo; // Tiempo de descubrimiento inicial

    for (int u : ady[v]) {
        if (estado[u] == 0) { // Si aún no visitamos el nodo
            padre[u] = v;
            dfs(u);

            // Actualiza el valor bajo (low-link) del nodo actual
            low[v] = min(low[v], low[u]);

            // Si la condición se cumple, (v, u) es un puente
            if (low[u] > discovery[v]) {
                puentes.push_back({v, u});
            }
        } else if (u != padre[v]) {
            // Si `u` ya fue visto y no es el padre de `v`, actualizamos `low[v]`
            low[v] = min(low[v], discovery[u]);
        }
    }
}



int main() {
    int n = 4;  // número de nodos
    ady.assign(n, vector<int>());
    estado.assign(n, 0);
    padre.assign(n, -1);
    discovery.assign(n, -1);
    low.assign(n, -1);
    tiempo = 0;

    // Construcción del grafo
    ady[2].push_back(3); ady[3].push_back(2); 
    // ady[1].push_back(2); ady[2].push_back(1);
    // ady[1].push_back(3); ady[3].push_back(1);
    // ady[0].push_back(2); ady[2].push_back(0);

    // Realiza DFS a partir del nodo 0
    for (int i = 0; i < n; i++) {
        if (estado[i] == 0) {
            dfs(i);
        }
    }

    // Imprime las aristas que son puentes
    cout << "Aristas que son puentes:" << endl;
    for (auto [u, v] : puentes) {
        cout << "(" << u << ", " << v << ")" << endl;
    }

    return 0;
}
