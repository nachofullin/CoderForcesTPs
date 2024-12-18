#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <utility>



using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }
 
    int findSet(int node){
 
        // En caso que nodo sea el representante
        if (node == parent[node]) return node;
 
        // Hago path compression
        return parent[node] = findSet(parent[node]);
    }
 
    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);
 
        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;
 
        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

vector<vector<int>> ady;
vector<int> estado, padre, discovery, low;
unordered_map<int, unordered_map<int, bool>> puentes;
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
                puentes[v][u] = true;
                puentes[u][v] = true;
            }
        } else if (u != padre[v]) {
            // Si `u` ya fue visto y no es el padre de `v`, actualizamos `low[v]`
            low[v] = min(low[v], discovery[u]);
        }
    }
}

int main() {
    int n, a;
    cin >> n;   //cant de nodos
    cin >> a;   //cant aristas

    vector<tuple<int, int, int, int>> aristas(a);      //cada arista = (peso/w, vertice1/u, vertice2/v, indice)
    
    for (int i = 0; i < a; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        aristas[i] = make_tuple(w, u - 1, v - 1, i);   //resto 1 para manejar bien los indices
    }

    sort(aristas.begin(), aristas.end());   //ordeno las aristas por peso de menor a mayor
    vector<string> res(a, "at least one");  //resultado de cada arista
    
    DisjointSet dsu(n);

    int i = 0;
    while (i < a) {
        ady.assign(n, vector<int>());
        estado.assign(n, 0);
        padre.assign(n, -1);
        discovery.assign(n, -1);
        low.assign(n, -1);
        tiempo = 0;
        

        int pesoActual = get<0>(aristas[i]);
        vector<tuple<int, int, int>> aristasPesoIgual; //armo vector con las aristas de mismo peso que voy a ir agregando
        
        while (i < a && get<0>(aristas[i]) == pesoActual) {
            aristasPesoIgual.emplace_back(get<1>(aristas[i]), get<2>(aristas[i]), get<3>(aristas[i]));
            ++i;
        }

        //printVectorOfTuples(aristasPesoIgual);
        
        for  (auto [u, v, indice] : aristasPesoIgual) {
            if (dsu.findSet(u) == dsu.findSet(v)) {
                res[indice] = "none";
            } else { 
                ady[dsu.findSet(u)].push_back(dsu.findSet(v));        //voy armando las adyacencias del grafo nuevo
                ady[dsu.findSet(v)].push_back(dsu.findSet(u));
            }
        }

        for (auto [u, v, indice] : aristasPesoIgual) {
            if (estado[dsu.findSet(u)] == 0) {
                dfs(dsu.findSet(u));
            }
            if (estado[dsu.findSet(v)] == 0) {
                dfs(dsu.findSet(v));
            }
        } //hago dfs recorro el grafo nuevo

        for (auto [u, v, indice] : aristasPesoIgual) {
            
            if (puentes[dsu.findSet(u)][dsu.findSet(v)] == true) {
                res[indice] = "any";
            }
            dsu.unionByRank(dsu.findSet(u), dsu.findSet(v));
        }

    }
    
    for (const auto& resultado : res) {
        cout << resultado << endl; // Imprimir resultados
    }
}