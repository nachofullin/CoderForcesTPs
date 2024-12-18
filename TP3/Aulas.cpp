#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
#include <string.h>
#include <queue>

using namespace std;

const int INF = 1000000000;
const int V = 202;

int grafo[V][V];
int rGraph[V][V];


//Los algoritmos de bfs y fordFulkerson fueron sacados de https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
bool bfs(int graph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && graph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
     // Residual graph where rGraph[i][j]
                   // indicates residual capacity of edge
                   // from i to j (if there is an edge. If
                   // rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];
 
    int parent[V]; // This array is filled by BFS and to
                   // store path
 
    int max_flow = 0; // There is no flow initially
 
    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n+1), b(n+1);
    int totalA = 0, totalB = 0;

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        totalA += a[i];
    }
    
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        totalB += b[i];
    }

    if (totalA != totalB) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        grafo[p][q+n] = INF;
        grafo[q][p+n] = INF;
    }

    for (int i = 1; i <= n; i++) {
        grafo[0][i] = a[i];
        grafo[n+i][2*n+1] = b[i];
        grafo[i][i+n] = INF;
    }

    // cout << "Matriz de capacidades:\n";
    // for (int i = 0; i <= 2*n + 1; ++i) {
    //     for (int j = 0; j <= 2*n + 1; ++j) {
    //         if (grafo[i][j] == INF)
    //             cout << "INF ";
    //         else
    //             cout << grafo[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    int maxFlow = fordFulkerson(grafo, 0, 2*n+1);

    if (maxFlow != totalB) {
        cout << "NO\n";
        return 0;
    }

    // cout << "Matriz de residuo:\n";
    // for (int i = 0; i <= 2*n + 1; ++i) {
    //     for (int j = 0; j <= 2*n + 1; ++j) {
    //         if (rGraph[i][j] == INF)
    //             cout << "INF ";
    //         else
    //             cout << rGraph[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {

            cout << rGraph[j+n][i] << " ";


        }
        cout << "\n";
    }

}