#include <bits/stdc++.h>
using namespace std;

using Cell = vector<int>;
using Row  = vector<Cell>;
using Grid = vector<Row>;

static void fold_vertical(Grid &g, int k) {
    int H = (int)g.size();
    int W = (int)g[0].size();
    int L = W - k;           // columns on the left of fold line
    int R = k;               // columns on the right of fold line
    Grid ng(H);

    for (int r = 0; r < H; ++r) {
        vector<Row::value_type> left(L), right(R);
        for (int c = 0; c < L; ++c) left[c] = g[r][c];
        for (int c = 0; c < R; ++c) right[c] = g[r][L + c];
        reverse(right.begin(), right.end()); // fold brings right part reversed (left-to-right)

        Row nr;
        if (L > R) {
            // extra left columns remain
            for (int i = 0; i < L - R; ++i) nr.push_back(left[i]);
            for (int i = 0; i < R; ++i) {
                Cell merged = left[L - R + i];
                // right section placed over left -> append right on top
                merged.insert(merged.end(), right[i].begin(), right[i].end());
                nr.push_back(move(merged));
            }
        } else {
            // extra right columns extend beyond to the left
            for (int i = 0; i < R - L; ++i) nr.push_back(right[i]);
            for (int i = 0; i < L; ++i) {
                Cell merged = left[i];
                merged.insert(merged.end(), right[R - L + i].begin(), right[R - L + i].end());
                nr.push_back(move(merged));
            }
        }
        ng[r] = move(nr);
    }
    g.swap(ng);
}

static void fold_horizontal(Grid &g, int k) {
    int H = (int)g.size();
    int W = (int)g[0].size();
    int T = H - k;           // rows above the fold line
    int B = k;               // rows below the fold line
    Grid ng;

    vector<Row> top(T), bot(B);
    for (int r = 0; r < T; ++r) top[r] = g[r];
    for (int r = 0; r < B; ++r) bot[r] = g[T + r];
    reverse(bot.begin(), bot.end()); // fold brings bottom part reversed (top-to-bottom)

    if (T > B) {
        // extra top rows remain
        for (int i = 0; i < T - B; ++i) ng.push_back(top[i]);
        for (int i = 0; i < B; ++i) {
            Row row = top[T - B + i];
            for (int c = 0; c < W; ++c) {
                // bottom over top -> append bottom on top
                row[c].insert(row[c].end(), bot[i][c].begin(), bot[i][c].end());
            }
            ng.push_back(move(row));
        }
    } else {
        // extra bottom rows extend above
        for (int i = 0; i < B - T; ++i) ng.push_back(bot[i]);
        for (int i = 0; i < T; ++i) {
            Row row = top[i];
            for (int c = 0; c < W; ++c) {
                row[c].insert(row[c].end(), bot[B - T + i][c].begin(), bot[B - T + i][c].end());
            }
            ng.push_back(move(row));
        }
    }
    g.swap(ng);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C;
    if (!(cin >> R >> C)) return 0;
    string rest;
    getline(cin, rest); // consume endline

    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<string> ops;
    string tok;
    while (ss >> tok) ops.push_back(tok);

    Grid g(R, Row(C));
    int id = 1;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            g[i][j] = Cell{ id++ };

    for (auto &op : ops) {
        if (op.empty()) continue;
        char t = op[0];
        int k = stoi(op.substr(1));
        if (t == 'v') {
            int W = (int)g[0].size();
            if (k <= 0 || k >= W) { cout << "0 0\n"; return 0; }
            fold_vertical(g, k);
        } else if (t == 'h') {
            int H = (int)g.size();
            if (k <= 0 || k >= H) { cout << "0 0\n"; return 0; }
            fold_horizontal(g, k);
        }
    }


    int topId = -1, bottomId = -1;
    for (int i = 0; i < (int)g.size(); ++i) {
        for (int j = 0; j < (int)g[0].size(); ++j) {
            if (!g[i][j].empty()) {
                bottomId = g[i][j].front();
                topId = g[i][j].back();
                
                goto done;
            }
        }
    }
done:
    cout << topId << " " << bottomId << "\n";
    return 0;
}
