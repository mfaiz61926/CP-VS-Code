#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        long long N, M;
        cin >> N >> M;

        bool ok = false;
        if (N >= M && N <= 2LL * M - 2) ok = true;
        else if (N >= 2LL * M && (N % 2 == 0)) ok = true;

        cout << "Case #" << tc << ": " << (ok ? "YES" : "NO") << "\n";
    }

    return 0;
}
