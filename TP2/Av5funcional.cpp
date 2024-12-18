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
////////////////////////////////////////
int N, M, U[100000], V[100000], W[100000], C[100000], ans[100000];
vector<int> I[1000001];
vector<pair<int, int>> graph[100000];
bool vis[100000];
int in[100000], lo_in[100000], gt;

void dfs(int v, int p){
	vis[v] = 1;
	in[v] = lo_in[v] = gt++;
	for(pair<int, int> i : graph[v]){
		int c = i.first, id = i.second;
		if(id == p) continue;
		if(vis[c]){
			lo_in[v] = min(lo_in[v], in[c]);
			if(lo_in[c] > in[v]){
				ans[id] = 2;
			}
			continue;
		}
		dfs(c, id);
		lo_in[v] = min(lo_in[v], lo_in[c]);
		if(lo_in[c] > in[v]){
			ans[id] = 2;
		}
	}
}

int32_t main(){
	cin.tie(0) -> sync_with_stdio(0);
	cin >> N >> M;
	for(int i = 0; i < M; i++){
		cin >> U[i] >> V[i] >> W[i];
		U[i]--, V[i]--;
		I[W[i]].push_back(i);
	}
	DisjointSet dsu(N);
	for(int i = 0; i <= 1000000; i++){
		if(!I[i].size()) continue;
		for(int j : I[i]){
			int u = dsu.findSet(U[j]), v = dsu.findSet(V[j]);
			if(u != v){
				graph[u].push_back({v, j});
				graph[v].push_back({u, j});
				ans[j] = 1;
			}
		}
		gt = 0;
		for(int j : I[i]){
			int u = dsu.findSet(U[j]), v = dsu.findSet(V[j]);
			if(vis[u] || vis[v]) continue;
			dfs(u, -1);
			dfs(v, -1);
		}
		for(int j : I[i]){
			int u = dsu.findSet(U[j]), v = dsu.findSet(V[j]);
			graph[u].clear(), graph[v].clear();
			vis[u] = 0, vis[v] = 0;
		}
		for(int j : I[i]){
			dsu.unionByRank(U[j], V[j]);
		}
	}
	for(int i = 0; i < M; i++){
		if(ans[i] == 0) cout << "none";
		if(ans[i] == 1) cout << "at least one";
		if(ans[i] == 2) cout << "any";
		cout << endl;
	}
}