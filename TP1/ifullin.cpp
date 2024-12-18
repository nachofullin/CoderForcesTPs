#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>  // Para std::pair

using namespace std;

bool comparador(pair<int, int> elem1, pair<int, int> elem2) {
    return elem1.second < elem2.second; 
}

int busyman(vector<pair<int, int>> actividades, int n) {
    sort(actividades.begin(), actividades.end(), comparador);  //ordeno por finalizacion de actividad

    int res = 1;    //una siemrpe vas a poder meter (la primera)

    pair<int, int> actual = actividades[0];

    for (int i = 1; i < n; i++) {
        if (actual.second <= actividades[i].first) {
            actual = actividades[i];
            res++;
        }
    }
    return res;
}

int main () {
    int t;
    cin >> t;   //cant de test cases

    while (t > 0) {
        int n;
        cin >> n;   //cant de actividades

        vector<pair<int, int>> actividades(n);  //vector de duplas para las actividades (inicio y fin)
        for (int i = 0; i < n; i ++) {
            cin >> actividades[i].first;    //inicio    
            cin >> actividades[i].second;   //fin
        }

        cout << busyman(actividades, n) << endl;

        t--;
    }
}