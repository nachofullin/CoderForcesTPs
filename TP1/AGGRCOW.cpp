#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool es_posible(vector<int>& stalls, int c, int dist, int n) {
    c--;    //coloco la primera vaca (minimo una tiene q entrar)
    int ultima_posicion = stalls[0];

    for (int i = 1; i < n; i++) {
        if (stalls[i] - ultima_posicion >= dist) {
            c--;    //coloco una vaca
            ultima_posicion = stalls[i];
        }
        if (c == 0) {
            return true;
        }
    }
    return false;
}

int aggrcow(vector<int>& stalls, int c, int n) { //busqueda binaria para ir probando varias distancias hasta llegar a la mejor
    sort(stalls.begin(), stalls.end());     //ordeno los establos de menor a mayor

    int min_dist = 1;
    int max_dist = stalls[n-1] - stalls[0];
    int mejor_dist = 0;

    while (min_dist <= max_dist) {
        int mid_dist = min_dist + (max_dist - min_dist) / 2;
        
        if (es_posible(stalls, c, mid_dist, n)) {
            mejor_dist = mid_dist;
            min_dist = mid_dist + 1;
        } else {
            max_dist = mid_dist - 1;
        }
    }
    return mejor_dist;
}

int main () {
    int t;
    cin >> t;   //cant de test cases

    while (t > 0) {
        int n, c;
        cin >> n;      // cant stalls
        cin >> c;      // cows

        vector<int> stalls(n);
        for (int i = 0; i < n; i ++) {
            cin >> stalls[i];
        }

        cout << aggrcow(stalls, c, n) << endl;

        t--;
    }
}