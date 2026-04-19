// Midnight Code Cup 2026 - Problem A: Beutsche Dahn
// C++11 compatible
// Strategy:
//   BFS all-pairs shortest paths, greedy train assignment per tradesman,
//   tick-by-tick simulation with edge-collision avoidance.

#include <bits/stdc++.h>
using namespace std;

// ── Graph ────────────────────────────────────────────────────────────────────
int V, E, T_cnt, C, N;
vector<vector<int>> adj;
vector<vector<int>> dist_mat; // dist_mat[s][v]
vector<vector<int>> prev_mat; // prev_mat[s][v] = predecessor of v on BFS tree from s

void bfs(int src) {
    vector<int>& d = dist_mat[src];
    vector<int>& pr = prev_mat[src];
    d.assign(V + 1, INT_MAX);
    pr.assign(V + 1, -1);
    queue<int> q;
    d[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int w : adj[u]) {
            if (d[w] == INT_MAX) {
                d[w] = d[u] + 1;
                pr[w] = u;
                q.push(w);
            }
        }
    }
}

vector<int> getPath(int src, int dst) {
    if (src == dst) return vector<int>(1, src);
    vector<int> path;
    int cur = dst;
    while (cur != src) {
        path.push_back(cur);
        cur = prev_mat[src][cur];
        if (cur == -1) return vector<int>();
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}

// ── Main ─────────────────────────────────────────────────────────────────────
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E;
    adj.resize(V + 1);
    for (int i = 0; i < E; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cin >> T_cnt;
    vector<int> trainPos(T_cnt);
    for (int i = 0; i < T_cnt; i++) cin >> trainPos[i];
    cin >> C;
    cin >> N;

    vector<int> tm_u(N), tm_v(N), tm_t(N);
    for (int i = 0; i < N; i++) cin >> tm_u[i] >> tm_v[i] >> tm_t[i];

    // BFS from every city
    dist_mat.resize(V + 1, vector<int>(V + 1, INT_MAX));
    prev_mat.resize(V + 1, vector<int>(V + 1, -1));
    for (int s = 1; s <= V; s++) bfs(s);

    // ── Greedy assignment ────────────────────────────────────────────────────
    // For each tradesman (in appearance order), pick train minimising drop tick.
    struct Plan {
        int tradesmanId; // 0-based
        int trainId;     // 0-based
    };

    vector<int> trAvailTick(T_cnt, 1);
    vector<int> trAvailCity(T_cnt);
    for (int i = 0; i < T_cnt; i++) trAvailCity[i] = trainPos[i];

    vector<vector<Plan>> trainPlans(T_cnt);

    for (int i = 0; i < N; i++) {
        int ui = tm_u[i], vi = tm_v[i], ti = tm_t[i];

        int bestTrain = -1, bestDrop = INT_MAX;
        for (int tr = 0; tr < T_cnt; tr++) {
            int avC = trAvailCity[tr], avT = trAvailTick[tr];
            if (dist_mat[avC][ui] == INT_MAX || dist_mat[ui][vi] == INT_MAX) continue;
            int arrUi = (avC == ui) ? max(ti, avT) : max(ti, avT + dist_mat[avC][ui]);
            int drop  = arrUi + dist_mat[ui][vi];
            if (drop < bestDrop) { bestDrop = drop; bestTrain = tr; }
        }
        if (bestTrain == -1) continue;

        int avC = trAvailCity[bestTrain], avT = trAvailTick[bestTrain];
        int arrUi = (avC == ui) ? max(ti, avT) : max(ti, avT + dist_mat[avC][ui]);
        int drop  = arrUi + dist_mat[ui][vi];

        Plan p; p.tradesmanId = i; p.trainId = bestTrain;
        trainPlans[bestTrain].push_back(p);

        trAvailCity[bestTrain] = vi;
        trAvailTick[bestTrain] = drop + 1;
    }

    // ── Simulate tick-by-tick with collision avoidance ───────────────────────
    // reservedEdges[tick] = set of undirected edges {min,max} already used
    map<int, set<pair<int,int>>> reserved;

    struct ActionRec { int tick; int type; int trainId; int tradesmanId; }; // type 0=pick,1=drop
    struct MoveRec   { int tick; int trainId; int destCity; };

    vector<ActionRec> actionRecs;
    vector<MoveRec>   moveRecs;

    int finalTick = 1;

    auto reserveMove = [&](int& curTick, int from, int to, int trainId1) {
        pair<int,int> edge = make_pair(min(from,to), max(from,to));
        while (reserved[curTick].count(edge)) ++curTick;
        reserved[curTick].insert(edge);
        MoveRec mr; mr.tick = curTick; mr.trainId = trainId1; mr.destCity = to;
        moveRecs.push_back(mr);
        finalTick = max(finalTick, curTick);
        ++curTick;
    };

    for (int tr = 0; tr < T_cnt; tr++) {
        int curCity = trainPos[tr];
        int curTick = 1;

        for (int pi = 0; pi < (int)trainPlans[tr].size(); pi++) {
            int tid = trainPlans[tr][pi].tradesmanId;
            int ui = tm_u[tid], vi = tm_v[tid], ti = tm_t[tid];

            // Move to pickup city
            if (curCity != ui) {
                vector<int> path = getPath(curCity, ui);
                for (int k = 0; k + 1 < (int)path.size(); k++) {
                    reserveMove(curTick, path[k], path[k+1], tr + 1);
                    curCity = path[k+1];
                }
            }

            // Wait for tradesman
            if (curTick < ti) curTick = ti;

            // Pick
            ActionRec ar; ar.tick = curTick; ar.type = 0; ar.trainId = tr + 1; ar.tradesmanId = tid + 1;
            actionRecs.push_back(ar);
            finalTick = max(finalTick, curTick);

            // Move to destination
            if (curCity != vi) {
                vector<int> path = getPath(curCity, vi);
                for (int k = 0; k + 1 < (int)path.size(); k++) {
                    reserveMove(curTick, path[k], path[k+1], tr + 1);
                    curCity = path[k+1];
                }
            }

            // Drop
            ActionRec dr; dr.tick = curTick; dr.type = 1; dr.trainId = tr + 1; dr.tradesmanId = tid + 1;
            actionRecs.push_back(dr);
            finalTick = max(finalTick, curTick);
        }
    }

    finalTick = min(finalTick, 999999);

    // ── Build per-tick output ────────────────────────────────────────────────
    struct TickOut {
        vector<ActionRec> acts;
        vector<MoveRec>   mvs;
    };
    vector<TickOut> out(finalTick + 1);

    for (int i = 0; i < (int)actionRecs.size(); i++) {
        int t2 = actionRecs[i].tick;
        if (t2 >= 1 && t2 <= finalTick) out[t2].acts.push_back(actionRecs[i]);
    }
    for (int i = 0; i < (int)moveRecs.size(); i++) {
        int t2 = moveRecs[i].tick;
        if (t2 >= 1 && t2 <= finalTick) out[t2].mvs.push_back(moveRecs[i]);
    }

    // Within each tick: drops before picks
    for (int t2 = 1; t2 <= finalTick; t2++) {
        stable_sort(out[t2].acts.begin(), out[t2].acts.end(),
            [](const ActionRec& a, const ActionRec& b) {
                return a.type > b.type; // drop(1) before pick(0)
            });
    }

    // ── Print ────────────────────────────────────────────────────────────────
    cout << finalTick << "\n";
    for (int t2 = 1; t2 <= finalTick; t2++) {
        cout << out[t2].acts.size() << "\n";
        for (int a = 0; a < (int)out[t2].acts.size(); a++) {
            const ActionRec& ar = out[t2].acts[a];
            cout << (ar.type == 0 ? "pick" : "drop") << " "
                 << ar.trainId << " " << ar.tradesmanId << "\n";
        }
        cout << out[t2].mvs.size() << "\n";
        for (int m = 0; m < (int)out[t2].mvs.size(); m++) {
            const MoveRec& mr = out[t2].mvs[m];
            cout << mr.trainId << " " << mr.destCity << "\n";
        }
    }

    return 0;
}