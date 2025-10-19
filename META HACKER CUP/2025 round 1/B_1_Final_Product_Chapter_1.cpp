#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        long long N, A, B;
        cin >> N >> A >> B;

        vector<long long> ans;
        ans.reserve(2 * N);
        // First N days: 1
        for (long long i = 0; i < N; ++i) ans.push_back(1);
        // Next N-1 days: 1
        for (long long i = 0; i < N - 1; ++i) ans.push_back(1);
        // Last day: B
        ans.push_back(B);

        cout << "Case #" << tc << ": ";
        for (size_t i = 0; i < ans.size(); ++i) {
            if(!i)cout << ans[i];
            if (i) cout << ' ';

        }
        cout << '\n';
    }
    return 0;
}
