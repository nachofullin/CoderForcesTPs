#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main () {
    int n;
    cin >> n;   

    vector<vector<long long>> dist(n, vector<long long>(n));
    int longuitud;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> longuitud;
            dist[i][j] = longuitud;
        }
    }

    vector<int> orden(n);
    for (int i = 0; i < n; i++) {
        cin >> orden[i];
        orden[i]--;     //lo pasamos a indice 0
    }
    vector<long long> res(n);
    vector<bool> activo(n, false);

    for (int k = n - 1; k >= 0; k--) {
        int nodo = orden[k];
        activo[nodo] = true;
        
        long long total = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][nodo] + dist[nodo][j]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (!activo[i]) continue;
            for (int j = 0; j < n; j++) {
                if (!activo[j]) continue;
                total += dist[i][j];
            }
        }
        res[k] = total;
    }
    
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
}