#include <bits/stdc++.h>
using namespace std;

// int main_conq() {

//     int n;
//     cin >> n;

//     vector<int> a(n);

//     for(int i = 0; i < n; i++)
//         cin >> a[i];


//     int ans = INT_MIN;


//     for(int i = 0; i < n; i++) {

//         int sum = 0;

//         for(int j = i; j < n; j++) {

//             sum += a[j];

//             ans = max(ans, sum);
//         }
//     }


//     cout << ans << "\n";

//     return 0;
// }

int main(){
    int n;
    cin >> n;

    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += i;
    }
    cout << ans << endl;
    return 0;
}