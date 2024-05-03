#include <bits/stdc++.h>
using namespace std;

const int MAXX = 100000000;
const int gsize = 6; //graph size
//find augmenting path in residual network using dfs:
int dfs(int graph[gsize][gsize], int source, int sink, int min_capacity, bool visited[]) {
    visited[source] = true;
    if (source == sink)
        return min_capacity;
    for (int node = 0; node < gsize; node++) {
        if (!visited[node] && graph[source][node] > 0) {
            int flow = dfs(graph, node, sink, min(min_capacity, graph[source][node]), visited);
            //update residual network:
            if (flow > 0) {
                graph[source][node] = graph[source][node] - flow;
                graph[node][source] = graph[node][source] + flow;
                return flow;
            }
        }
    }
    return 0;
}
int ford_fulkerson(int graph[gsize][gsize], int source, int sink) {
    int u, node;
    int resgraph[gsize][gsize]; //residual network
    for (u = 0; u < gsize; u++)
        for (node = 0; node < gsize; node++)
            resgraph[u][node] = graph[u][node]; //copy initial graph
    int max_flow = 0;
    // ищем дополняющий путь используя dfs, если не находим, выходим из цикла:
    while (true) {
        bool visited[gsize];
        memset(visited, 0, sizeof(visited));
        int path_flow = dfs(graph, source, sink, MAXX, visited);
        if (path_flow == 0)
            break;
        max_flow += path_flow;
    }
    return max_flow;
}
int main() {
    //adjacency matrix
    int graph[gsize][gsize] = { {0, 7, 4, 0, 0,0},
                        {0, 0, 4, 0, 2,0},
                        {0, 0, 0, 4, 8,0},
                        {0, 0, 0, 0, 0,0},
                        {0, 0, 0, 0, 0,12},
                        {0,0,0,0,0,0}
    };

    cout << "max flow: " << ford_fulkerson(graph, 0, 5);

    return 0;
}
