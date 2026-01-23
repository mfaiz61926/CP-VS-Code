#include <bits/stdc++.h>
using namespace std;
// int cntIncreasingSubarray(vector<int>&v){
//     int n = v.size();
//     long long total = 0;
//     int len = 1;
//     const int MOD = 1e9 + 7;
//     for(int i = 1; i < n; i++){
//         if(i < n && v[i] > v[i - 1]){
//             len++;
//         }
//         else{
//             total += (len * (len + 1) / 2) % MOD;
//             len = 1;
//         }
//     }
//     total += (1LL * len * (len + 1) / 2) % MOD;

//     return total;

// }

int cntIncreasingSubarray(vector<int>&v){
    int n = v.size();
    long long total = 0;
    int len = 1;
    const int MOD = 1e9 + 7;
    for(int i = 1; i <= n; i++){
        if(i < n && v[i] > v[i - 1]){
            len++;
        }
        else{
            total += (len * (len + 1) / 2) % MOD;
            if(i < n){
                len = 1;
            }
        }
    }

    return total % MOD;

}

int main() {
    int n;
    cin >> n;
    vector<int>v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    int ans = cntIncreasingSubarray(v);
    cout << ans << endl;
    return 0;
}