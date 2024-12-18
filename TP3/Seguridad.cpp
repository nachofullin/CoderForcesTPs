#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int INF = 1000000000;

vector<int> dijkstra(int start, int n, const vector<vector<pair<int, int>>>& ady) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});  // (distancia, nodo)
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto edge : ady[u]) {
            int v = edge.first;
            int c = edge.second;
            if (dist[u] + c < dist[v]) {
                dist[v] = dist[u] + c;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}


int main () {
    int n, m;
    cin >> n >> m;   //cant de aristas

    vector<vector<pair<int, int>>> ady(n), adyInvertida(n);

    while (m > 0) {
        int v, w, c;
        cin >> v;      
        cin >> w;      
        cin >> c;

        ady[v].emplace_back(w, c);
        ady[w].emplace_back(v, c);
        adyInvertida[w].emplace_back(v, c);

        m--;
    }

    vector<int> dist_desde_0 = dijkstra(0, n, ady);
    vector<int> dist_desde_n = dijkstra(n-1, n, ady);

    int res = 0;
    int minimo = dist_desde_0[n-1];

    for (int v = 0; v < n; ++v) {
        for (auto edge : ady[v]) {
            int w = edge.first;
            int c = edge.second;
            if (dist_desde_0[v] + c + dist_desde_n[w] == minimo) {
                res += c;
            }
        }
    }

    cout << 2 * res << endl;
}