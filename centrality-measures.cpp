#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Function to calculate degree centrality
vector<double> calculateDegreeCentrality(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<double> degreeCentrality(n, 0.0);

    for (int i = 0; i < n; i++) {
        degreeCentrality[i] = graph[i].size();
    }

    return degreeCentrality;
}

// Function to calculate shortest paths from a given node to all other nodes
vector<int> calculateShortestPaths(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;
    visited[start] = true;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        for (int neighbor : graph[currNode]) {
            if (!visited[neighbor]) {
                dist[neighbor] = dist[currNode] + 1;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return dist;
}

// Function to calculate closeness centrality
vector<double> calculateClosenessCentrality(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<double> closenessCentrality(n, 0.0);

    for (int i = 0; i < n; i++) {
        vector<int> shortestPaths = calculateShortestPaths(graph, i);
        double sumDist = 0.0;

        for (int dist : shortestPaths) {
            if (dist != -1) {
                sumDist += dist;
            }
        }

        closenessCentrality[i] = 1.0 / sumDist;
    }

    return closenessCentrality;
}

// Function to calculate betweenness centrality
vector<double> calculateBetweennessCentrality(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<double> betweennessCentrality(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                vector<int> shortestPaths = calculateShortestPaths(graph, i);
                int countShortestPaths = 0;

                for (int dist : shortestPaths) {
                    if (dist == shortestPaths[j] - 1) {
                        countShortestPaths++;
                    }
                }

                betweennessCentrality[i] += (double)countShortestPaths / n;
            }
        }
    }

    return betweennessCentrality;
}

int main() {
    int n; // Number of nodes
    int m; // Number of edges

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> m;

    vector<vector<int>> graph(n);

    cout << "Enter the edges (node u to node v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<double> degreeCentrality = calculateDegreeCentrality(graph);
    vector<double> closenessCentrality = calculateClosenessCentrality(graph);
    vector<double> betweennessCentrality = calculateBetweennessCentrality(graph);

    cout << "Degree Centrality:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << degreeCentrality[i] << endl;
    }

    cout << "Closeness Centrality:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << closenessCentrality[i] << endl;
    }

    cout << "Betweenness Centrality:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << betweennessCentrality[i] << endl;
    }

    return 0;
}
