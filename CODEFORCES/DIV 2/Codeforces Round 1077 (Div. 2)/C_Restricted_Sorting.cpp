#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        vector<int> b = a;
        sort(b.begin(), b.end());
        
        if (a == b) {
            cout << "-1\n";
            continue;
        }
        
        map<int, vector<int>> pos;
        for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
        for (auto &p : pos) sort(p.second.begin(), p.second.end());
        
        map<int, int> ptr;
        int ans = INT_MAX;
        int mx = -1;
        
        for (int i = 0; i < n; i++) {
            int idx = pos[b[i]][ptr[b[i]]++];
            if (idx < mx) {
                int j = i;
                while (j + 1 < n && b[j + 1] == b[i]) j++;
                if (j + 1 < n) ans = min(ans, b[j + 1] - b[i]);
            }
            mx = max(mx, idx);
        }
        
        cout << (ans == INT_MAX ? 0 : ans) << "\n";
    }
    
    return 0;
}