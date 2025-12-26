#include <bits/stdc++.h>
using namespace std;

long long f(long long x) {
    // f(x) = x * (value of least significant set bit)
    // LSB value can be found using x & (-x)
    return x * (x & (-x));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        vector<long long> water(n + 1, 0);
        
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            
            for (int j = l; j <= r; j++) {
                water[j] += f(j - l + 1);
            }
        }
        
        for (int i = 1; i <= n; i++) {
            cout << water[i];
            if (i < n) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}