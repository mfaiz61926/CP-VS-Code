#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> far(n + 1);
        iota(far.begin(), far.end(), 1);
        far[n] = n;
        vector<int> indeg(n + 2, 0);
        for (int i = 1; i < n; ++i) indeg[i + 1]++;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            far[u] = max(far[u], v);
            indeg[v]++;
        }
        vector<int> cnt(n + 2, 0);
        for (int i = 1; i < n; ++i) cnt[far[i]]++;
        long long ans = 0;
        for (int v = 2; v <= n; ++v) ans += 1LL * cnt[v] * (indeg[v] - 1);
        cout << ans << '\n';
    }
    return 0;
}