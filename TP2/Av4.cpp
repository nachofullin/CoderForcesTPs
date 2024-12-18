#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>

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

vector<string> res;
int tiempo;

vector<vector<pair<int, int>>> ady(100000);
vector<bool> estado(100000);
vector<int> discovery, low;

void dfs(int v, int p){ //dfs de algortimo Tarjan
	estado[v] = 1;
	discovery[v] = low[v] = tiempo++;
	for(pair<int, int> i : ady[v]){
		int u = i.first, id = i.second;
		if(id == p) continue;
		if(estado[u]){
			low[v] = min(low[v], discovery[u]);
			if(low[u] > discovery[v]){
				res[id] = "any";        //si encuentro un puente modifico el res
			}
			continue;
		}
		dfs(u, id);
		low[v] = min(low[v], low[u]);
		if(low[u] > discovery[v]){
			res[id] = "any";        //si encuentro un puente modifico el res
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
    res.assign(a, "at least one");  //resultado de cada arista

    discovery.resize(n);
    low.resize(n);

    DisjointSet dsu(n);

    int i = 0;
    while (i < a) {
        int pesoActual = get<0>(aristas[i]);
        vector<tuple<int, int, int>> aristasPesoIgual; //armo vector con las aristas de mismo peso que voy a ir agregando

        while (i < a && get<0>(aristas[i]) == pesoActual) {
            aristasPesoIgual.emplace_back(get<1>(aristas[i]), get<2>(aristas[i]), get<3>(aristas[i]));
            ++i;
        }

        for  (auto [u, v, indice] : aristasPesoIgual) {
            if (dsu.findSet(u) == dsu.findSet(v)) {
                res[indice] = "none";
            } else { 
                ady[dsu.findSet(u)].push_back({dsu.findSet(v), indice});        //voy armando las adyacencias del grafo nuevo
                ady[dsu.findSet(v)].push_back({dsu.findSet(u), indice});
            }
        }
        tiempo = 0;
        for (auto [u, v, indice] : aristasPesoIgual) {
            if (estado[dsu.findSet(u)] == 0) {
                dfs(dsu.findSet(u), -1);
            }
            if (estado[dsu.findSet(v)] == 0) {
                dfs(dsu.findSet(v), -1);
            }
        } //hago dfs recorro el grafo nuevo

        for(auto [u, v, indice] : aristasPesoIgual){
			int u2 = dsu.findSet(u), v2 = dsu.findSet(v);
			ady[u2].clear(), ady[v2].clear();
			estado[u2] = 0, estado[v2] = 0;
		}

        for (auto [u, v, indice] : aristasPesoIgual) {
            dsu.unionByRank(u, v);
        }
    }
    
    for (const auto& resultado : res) {
        cout << resultado << endl; // imprimo los resultados
    }
}