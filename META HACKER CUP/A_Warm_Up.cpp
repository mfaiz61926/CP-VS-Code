#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<int> A(N), B(N);
        for (int i = 0; i < N; ++i) cin >> A[i];
        for (int i = 0; i < N; ++i) cin >> B[i];

        bool impossible = false;
        for (int i = 0; i < N; ++i)
            if (A[i] > B[i]) impossible = true;

        if (impossible) {
            cout << "Case #" << tc << ": -1\n";
            continue;
        }

        // Sort dishes by descending target temperature
        vector<int> order(N);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            return B[i] > B[j];
        });

        unordered_map<int, int> source; // temp -> index of one dish with that temp
        vector<pair<int, int>> ops;
        bool ok = true;

        for (int idx : order) {
            if (A[idx] == B[idx]) {
                source[B[idx]] = idx; // this dish can serve as a source
            } else {
                // Need to warm it up to B[idx]
                if (source.count(B[idx])) {
                    ops.push_back({source[B[idx]] + 1, idx + 1});
                    A[idx] = B[idx];
                } else {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            cout << "Case #" << tc << ": -1\n";
        } else {
            cout << "Case #" << tc << ": " << ops.size() << "\n";
            for (auto &p : ops)
                cout << p.first << " " << p.second << "\n";
        }
    }
    return 0;
}
