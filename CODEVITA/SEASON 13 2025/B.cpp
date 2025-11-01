#include <bits/stdc++.h>
using namespace std;

struct Race {
    int x, y, d;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<Race> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].d;
    }
    vector<vector<int>> adj(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a[j].d > a[i].d) {
                int dist = abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
                if (dist <= a[j].d - a[i].d) {
                    adj[i].push_back(j);
                }
            }
        }
    }

    // Kuhn's algorithm (DFS-based augmenting paths)
    vector<int> matchR(N, -1);
    function<bool(int, vector<char>&)> dfs = [&](int u, vector<char>& vis) -> bool {
        for (int v : adj[u]) {
            if (vis[v]) continue;
            vis[v] = 1;
            if (matchR[v] == -1 || dfs(matchR[v], vis)) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    };

    int M = 0;
    for (int u = 0; u < N; ++u) {
        vector<char> vis(N, 0);
        if (dfs(u, vis)) ++M;
    }

    cout << (N - M) << "\n";
    return 0;
}
