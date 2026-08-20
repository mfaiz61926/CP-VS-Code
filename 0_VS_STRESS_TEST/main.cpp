#include <bits/stdc++.h>
using namespace std;


// int main() {

//     int n;
//     cin >> n;

//     vector<int> a(n);

//     for(int &x : a)
//         cin >> x;


//     int ans = a[0];
//     int current = a[0];


//     for(int i = 1; i < n; i++) {

//         current = max(a[i], current + a[i]);

//         ans = max(ans, current);
//     }


//     cout << ans << "\n";

//     return 0;
// }

int main(){
    int n;
    cin >> n;
    cout << n * (n + 1) / 2 << endl;
}   