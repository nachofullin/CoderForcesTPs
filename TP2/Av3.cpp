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

struct Edge {
	int x, y, cost;
	Edge(int X, int Y, int Cost) { x = X; y = Y; cost = Cost; }
	bool operator < (const Edge b) const {
		return cost != b.cost ? cost < b.cost : (x < b.x || (x == b.x && y < b.y));
	}
};

vector<pair<Edge,int> > edges;
vector<string> answer;
DisjointSet dsu(100000);    //10 a la 5
vector<vector<int> > g;
vector<int> u, d, l;
int n, m, globalCounter;

void dfs(int v, int p = -1, int depth = 0) {
	l[v] = d[v] = depth;
	u[v] = globalCounter+1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (g[v][i] == p)continue;
		int id = g[v][i], x = dsu.findSet(edges[id].first.x);
        int y = dsu.findSet(edges[id].first.y);
        int to = x == v ? y : x;
		if (u[to]>globalCounter)
			l[v] = min(l[v], d[to]);
		else {
			dfs(to, g[v][i], depth+1);
			l[v] = min(l[v], l[to]);
		}

		if (l[to] > d[v]) {
			answer[edges[g[v][i]].second] = "any";
		}
	}
}

void solve() {
	cin >> n >> m;
	d.resize(n); l.resize(n); u.resize(n);
	g.assign(n, vector<int> ());
	answer.assign(m, "at least one");

	dsu = DisjointSet(n);
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		x--; y--;
		edges.push_back(make_pair(Edge(x,y,z),i));
	}

	sort(edges.begin(), edges.end());
	for (int i = 0; i < m;) {
		int k = i;
		while (k < (int)edges.size() && edges[k].first.cost == edges[i].first.cost)
			k++;
		for (int j = i; j < k; j++) {
			int x, y;
			x = dsu.findSet(edges[j].first.x);
			y = dsu.findSet(edges[j].first.y);

			if (x != y) {
				g[x].push_back(j);
				g[y].push_back(j);
			} else
				answer[edges[j].second] = "none";
		}

		for (int j = i; j < k; j++) {
			int x, y;
			x = dsu.findSet(edges[j].first.x);
			y = dsu.findSet(edges[j].first.y);
			if (u[x]<=globalCounter)
				dfs(x);
			if (u[y]<=globalCounter)
				dfs(y);
		}
		for (int j = i; j < k; j++) {
			int x, y;
			x = dsu.findSet(edges[j].first.x);
			y = dsu.findSet(edges[j].first.y);
			dsu.unionByRank(x, y);
			g[x].clear(); g[y].clear();
		}

		i = k;
		globalCounter++;
	}
	for (int i = 0; i < m; i++)
		cout << answer[i] << "\n";
}

int main() {
	solve();
	return 0;
}