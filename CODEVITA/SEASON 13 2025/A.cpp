#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define F              first
#define S              second
#define pb             push_back
#define si             set<long long>
#define vi             vector<long long>
#define pii            pair<long long, long long>
#define vpi            vector<pii>
#define endl           "\n"
#define sz(x)          ((int) x.size())
#define all(p)         p.begin(), p.end()

long long MOD = 1e9 + 7;

const int N = 200005;

// Rotate right 90°
vector<vector<char>> rightR(const vector<vector<char>>& box) {
    int m = box.size(), n = box[0].size();
    vector<vector<char>> res(n, vector<char>(m, '.'));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[j][m - 1 - i] = box[i][j];
        }
    }
    return res;
}

// Rotate left 90°
vector<vector<char>> leftR(const vector<vector<char>>& box) {
    int m = box.size(), n = box[0].size();
    vector<vector<char>> res(n, vector<char>(m, '.'));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[n - 1 - j][i] = box[i][j];
        }
    }
    return res;
}

// Apply gravity
void gravityA(vector<vector<char>>& box) {
    int m = box.size(), n = box[0].size();
    for (int j = 0; j < n; j++) {
        int empty = m - 1;
        for (int i = m - 1; i >= 0; i--) {
            if (box[i][j] == '*') {
                box[i][j] = '.';
                box[empty][j] = '*';
                empty--;
            }
        }
    }
}

void solve() {
    int m, n;
    cin >> m >> n;
    vector<vector<char>> mat(m, vector<char>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    int t;
    cin >> t;
    vector<string> op(t);
    for (int i = 0; i < t; i++) {
        cin >> op[i];
    }

    gravityA(mat);

    for (int i = 0; i < t; i++) {
        if (op[i] == "right") {
            mat = rightR(mat);
            gravityA(mat);
        } else if (op[i] == "left") {
            mat = leftR(mat);
            gravityA(mat);
        }
    }

    int r = mat.size();
    int c = mat[0].size();
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << mat[i][j];
            if (j + 1 < c) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
