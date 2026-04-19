#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int N, T;
int queries_left;

vector<vector<int>> known_cells;
vector<vector<bool>> candidate;
int cand_count;

int query(int r, int c) {
    if (queries_left <= 0) return -2;
    cout << r << " " << c << "\n";
    cout.flush();
    int resp;
    cin >> resp;
    queries_left--;
    if (resp == -1) {
        known_cells[r][c] = -1;
        candidate[r][c] = false;
    } else {
        known_cells[r][c] = 1;
    }
    return resp;
}

void reset_candidates() {
    cand_count = 0;
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= N; c++) {
            candidate[r][c] = (known_cells[r][c] != -1);
            if (candidate[r][c]) cand_count++;
        }
}

void us(int qr, int qc, int dist_val) {
    vector<vector<int>> d(N + 1, vector<int>(N + 1, -1));
    queue<pair<int,int>> q;
    d[qr][qc] = 0;
    q.push(make_pair(qr, qc));
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        if (d[r][c] >= dist_val) continue;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (known_cells[nr][nc] == -1) continue;
            if (d[nr][nc] != -1) continue;
            d[nr][nc] = d[r][c] + 1;
            q.push(make_pair(nr, nc));
        }
    }
    cand_count = 0;
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (!candidate[r][c]) continue;
            if (known_cells[r][c] == -1) { candidate[r][c] = false; continue; }
            if (d[r][c] != -1 && d[r][c] != dist_val) {
                candidate[r][c] = false;
            } else {
                cand_count++;
            }
        }
    }
}

pair<int,int> pick_query() {
    long long sr = 0, sc = 0, cnt = 0;
    for (int r = 1; r <= N; r++)
        for (int c = 1; c <= N; c++)
            if (candidate[r][c]) { sr += r; sc += c; cnt++; }
    if (cnt == 0) return make_pair(1, 1);
    int cr = (int)(sr / cnt), cc = (int)(sc / cnt);
    int best_r = -1, best_c = -1, best_d = INT_MAX;
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            if (!candidate[r][c]) continue;
            int dist = abs(r - cr) + abs(c - cc);
            if (dist < best_d) { best_d = dist; best_r = r; best_c = c; }
        }
    }
    return make_pair(best_r, best_c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(42);

    cin >> N >> T;
    queries_left = T;

    known_cells.assign(N + 1, vector<int>(N + 1, 0));
    candidate.assign(N + 1, vector<bool>(N + 1, true));
    cand_count = N * N;

    int step = 9;
    for (int r = 1; r <= N && queries_left > 8500; r += step) {
        for (int c = 1; c <= N && queries_left > 8500; c += step) {
            if (known_cells[r][c] != 0) continue;
            int resp = query(r, c);
            if (resp == 0) {
                reset_candidates();
            } else if (resp > 0) {
                us(r, c, resp);
            }
        }
    }

    while (queries_left > 10) {
        if (cand_count <= 1) reset_candidates();

        pair<int,int> pq = pick_query();
        int qr = pq.first, qc = pq.second;
        int resp = query(qr, qc);

        if (resp == -1) {
        } else if (resp == 0) {
            reset_candidates();
        } else {
            us(qr, qc, resp);

            int cur_r = qr, cur_c = qc, cur_dist = resp;
            while (cur_dist > 0 && queries_left > 10) {
                int order[4] = {0, 1, 2, 3};
                for (int i = 3; i > 0; i--) {
                    int j = rand() % (i + 1);
                    int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
                }

                bool moved = false;
                for (int ii = 0; ii < 4 && !moved; ii++) {
                    int i = order[ii];
                    int nr = cur_r + dr[i], nc = cur_c + dc[i];
                    if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
                    if (known_cells[nr][nc] == -1) continue; 

                    int nresp = query(nr, nc);
                    if (nresp == 0) {
                        reset_candidates();
                        cur_dist = 0;
                        moved = true;
                    } else if (nresp == -1) {
                    } else if (nresp < cur_dist) {
                        us(nr, nc, nresp);
                        cur_r = nr; cur_c = nc; cur_dist = nresp;
                        moved = true;
                    } else {
                        us(nr, nc, nresp);
                    }
                }
                if (!moved) break; 
            }
        }
    }

    cout << "-1 -1\n";
    cout.flush();
    return 0;
}