#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> ady;
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
vector<int> estado;
vector<int> memo;
vector<int> padre;
vector<vector<int>> tree_edges;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;

void dfs(int v, int p = -1) {
    estado[v] = EMPECE_A_VER;
    for (int u : ady[v]) {
        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            padre[u] = v;
            dfs(u, v);
        }
        else if (u != padre[v]) {
            
                back_edges_con_extremo_superior_en[u]++;
                back_edges_con_extremo_inferior_en[v]++;
            
            
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res += back_edges_con_extremo_superior_en[v];
    res -= back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
}

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Función para imprimir un vector de vectores de enteros
void printVectorOfVectors(const vector<vector<int>>& vecOfVecs) {
    cout << "[\n";
    for (size_t i = 0; i < vecOfVecs.size(); ++i) {
        printVector(vecOfVecs[i]);
        cout << (i != vecOfVecs.size() - 1 ? ",\n" : "\n");
    }
    cout << "]" << endl;
}

int main() {
    int n = 4;  // ejemplo: número de nodos
    ady.assign(n, vector<int>());
    estado.assign(n, NO_LO_VI);
    memo.assign(n, -1);
    padre.assign(n, -1);
    tree_edges.assign(n, vector<int>());
    back_edges_con_extremo_inferior_en.assign(n, 0);
    back_edges_con_extremo_superior_en.assign(n, 0);

    // Construye el grafo en `ady`
    ady[2].push_back(3); ady[3].push_back(2); 
    ady[1].push_back(2); ady[2].push_back(1);
    ady[1].push_back(3); ady[3].push_back(1);
    // ady[2].push_back(0); ady[0].push_back(2);
    
    
    vector<pair<int, int>> aristas;
    aristas.push_back({2, 3});
    aristas.push_back({2, 1});
    aristas.push_back({1, 3});
    // aristas.push_back({0, 2});
    
    printVectorOfVectors(ady);
    // Realiza DFS a partir del nodo 0
    for (int i = 0; i < n; i++) {
        if (estado[i] == 0) {
            dfs(i);
        }
    }

    vector<pair<int, int>> puentes;

    for (auto [u, v] : aristas) {
        cout << "padre de" << u << " = " << padre[u] << "| padre de " << v << " =" << padre[v] << endl;
        if ((cubren(u, v) == 0) || (cubren(v, u) == 0)) {
            puentes.push_back({u, v});
        }
    }

    for (int i = 0; i < n; i++) {
        // if (cubren(i, -1) == 0) {
        //     cout << "puente = " << i << ", " << padre[i] << endl;
        // }
        cout << "cubren(" << i << ", -1) = " << cubren(i, -1) << endl;
    }

    // Imprime las aristas que son puentes
    cout << "Aristas que son puentes:" << endl;
    for (auto [u, v] : puentes) {
        cout << "(" << u << ", " << v << ")" << endl;
    }

    return 0;
}
