#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> a(n, vector<int>(m));
        vector<vector<pair<int,int>>> pos(n*m + 1);
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> a[i][j];
                if(a[i][j] > 0) {
                    pos[a[i][j]].push_back({i, j});
                }
            }
        }
        
        long long ans = 0;
        
        for(int v = 1; v <= n*m; v++) {
            if(pos[v].size() < 2) continue;
            
            vector<pair<int,int>>& cells = pos[v];
            int sz = cells.size();
            
            for(int idx = 0; idx < sz; idx++) {
                auto [sx, sy] = cells[idx];
                
                // BFS: (x, y, dir, turns)
                // dir: 0=right, 1=down, 2=left, 3=up, 4=start
                queue<array<int,4>> q;
                q.push({sx, sy, 4, 0});
                
                bool visited[105][105][5][3] = {};
                visited[sx][sy][4][0] = true;
                
                while(!q.empty()) {
                    auto [x, y, dir, turns] = q.front();
                    q.pop();
                    
                    int dx[] = {0, 1, 0, -1};
                    int dy[] = {1, 0, -1, 0};
                    
                    for(int nd = 0; nd < 4; nd++) {
                        int nx = x + dx[nd];
                        int ny = y + dy[nd];
                        
                        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if(nx == sx && ny == sy) continue;
                        
                        if(a[nx][ny] == v) {
                            if(sx < nx || (sx == nx && sy < ny)) {
                                ans++;
                            }
                            continue;
                        }
                        
                        if(a[nx][ny] != 0) continue;
                        
                        int newTurns = turns;
                        if(dir != 4 && nd != dir) newTurns++;
                        
                        if(newTurns > 2) continue;
                        if(visited[nx][ny][nd][newTurns]) continue;
                        
                        visited[nx][ny][nd][newTurns] = true;
                        q.push({nx, ny, nd, newTurns});
                    }
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}