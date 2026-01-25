#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int n;
bool found = false;

// Function to perform DFS and query vertices
void dfs(int v, int parent) {
    if (found) return; // stop if we already found the vertex

    // Query the current vertex with itself
    cout << "? " << v << " " << v << endl;
    cout.flush();
    int res;
    cin >> res;

    if (res == 1) {
        // Found a vertex on the hidden path
        cout << "! " << v << endl;
        cout.flush();
        found = true;
        return;
    }

    for (int u : adj[v]) {
        if (u != parent) {
            dfs(u, v);
            if (found) return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // number of test cases
    while (t--) {
        cin >> n;
        adj.assign(n + 1, {}); // reset adjacency list
        found = false;

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Start DFS from vertex 1 (any vertex works)
        dfs(1, 0);
    }

    return 0;
}
