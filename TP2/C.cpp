#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<vector<int>> adyacencias, int s, vector<int>& dist) {
    queue<int> q;

    vector<bool> visited(adyacencias.size(), false);

    visited[s] = true;
    q.push(s);

    dist[s] = 0;

    while( !q.empty()) {
        int actual = q.front();
        q.pop();

        for (int vecino : adyacencias[actual]) {
            if(visited[vecino] == false) {
                visited[vecino] = true;
                q.push(vecino);
                dist[vecino] = dist[actual] + 1;    //marco la distacia a ese nodo como la anterior mas 1 (siendo bfs siempre sera el camino mas corto)
            }
        }
    }
}

int main() {
    int n;
    cin >> n;   //cant de nodos

    vector<vector<int>> adyacencias(n+1);

    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        if (i != u) {
            adyacencias[i].push_back(u);    //agrego el atajo (no hacerlo si i == u para no armar loops)
        }
        adyacencias[i].push_back(i+1);  //voy armando la secuencia 1-2-3-4-5-6-...-n
        adyacencias[i+1].push_back(i);
    }

    vector<int> dist(n+1);

    bfs(adyacencias, 1, dist);

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}