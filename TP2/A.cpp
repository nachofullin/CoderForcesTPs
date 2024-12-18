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
            padre[u]=v;
            dfs(u, v);
        }
        else if (u != padre[v]) {
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_superior_en[v]++;
            }
            else // estado[u] == TERMINE_DE_VER
                back_edges_con_extremo_inferior_en[v]++;
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p = -1) {
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


void printMemo(const vector<int>& memo) {
    for (size_t i = 0; i < memo.size(); ++i) {
        cout << "memo[" << i << "] = " << memo[i] << endl;
    }
}

void printTuple(const tuple<int, int, int>& t) {
    cout << "(" 
         << get<0>(t) << ", " 
         << get<1>(t) << ", " 
         << get<2>(t) << ")";
}

// Función para imprimir un vector de tuples
void printVectorOfTuples(const vector<tuple<int, int, int>>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        printTuple(vec[i]);
        if (i != vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Función para imprimir un vector de enteros
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
        tree_edges.assign(n, vector<int>());
        ady.assign(n, vector<int>());
        estado.assign(n, NO_LO_VI);
        memo.assign(n, -1);
        padre.assign(n, -1);
        back_edges_con_extremo_inferior_en.assign(n, 0);
        back_edges_con_extremo_superior_en.assign(n, 0);
        

        int pesoActual = get<0>(aristas[i]);
        vector<tuple<int, int, int>> aristasPesoIgual; //armo vector con las aristas de mismo peso que voy a ir agregando
        
        while (i < a && get<0>(aristas[i]) == pesoActual) {
            aristasPesoIgual.emplace_back(get<1>(aristas[i]), get<2>(aristas[i]), get<3>(aristas[i]));
            ++i;
        }

        // printVectorOfTuples(aristasPesoIgual);

        if (aristasPesoIgual.size() == 1) {
            res[get<2>(aristasPesoIgual[0])] = "any";
        }
        
        for  (auto [u, v, indice] : aristasPesoIgual) {
            if (dsu.findSet(u) == dsu.findSet(v)) {
                res[indice] = "none";
            } else { 
                ady[dsu.findSet(u)].push_back(dsu.findSet(v));        //voy armando las adyacencias del grafo nuevo
                ady[dsu.findSet(v)].push_back(dsu.findSet(u));
            }
        }

        printVectorOfVectors(ady);

        dfs(0); //hago dfs recorro el grafo nuevo

        for (auto [u, v, indice] : aristasPesoIgual) {
            // cout << "cubren(" << u << ", " << v << ") = " << cubren(u, v) << endl;
            if ((cubren(u) == 0 && padre[u] == v ) || (cubren(v) == 0 && padre[v] == u)) { //si cubre == 0  significa q es puente lo cambio en res
                res[indice] = "any";
                // cout << "puente = (" << u << ", " << v << ") " << endl;
            }
            dsu.unionByRank(u, v);
            // printMemo(memo);
        }

    }
    
    for (const auto& resultado : res) {
        cout << resultado << endl; // Imprimir resultados
    }
}