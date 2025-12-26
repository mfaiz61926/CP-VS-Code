// FIRST RUN
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode;
    cin >> mode; // "first"
    if (mode == "first")
    {
        int t;
        cin >> t;
        while (t--)
        {
            int n, m;
            cin >> n >> m;

            vector<vector<int>> adj(n + 1);
            for (int i = 0; i < m; i++)
            {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            vector<int> dist(n + 1, -1);
            queue<int> q;
            dist[1] = 0;
            q.push(1);

            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                for (int u : adj[v])
                {
                    if (dist[u] == -1)
                    {
                        dist[u] = dist[v] + 1;
                        q.push(u);
                    }
                }
            }

            string colors = "rgb";
            string ans(n, 'r');
            for (int i = 1; i <= n; i++)
            {
                ans[i - 1] = colors[dist[i] % 3];
            }

            cout << ans << "\n";
        }
    }
    else
    {
        int t;
        cin >> t;
        while (t--)
        {
            int q;
            cin >> q;

            while (q--)
            {
                int d;
                cin >> d;
                string s;
                cin >> s;

                vector<int> present(3, 0);
                for (char c : s)
                {
                    if (c == 'r')
                        present[0] = 1;
                    if (c == 'g')
                        present[1] = 1;
                    if (c == 'b')
                        present[2] = 1;
                }

                int target = -1;
                for (int c = 0; c < 3; c++)
                {
                    if (present[c] && !present[(c + 1) % 3])
                    {
                        target = c;
                        break;
                    }
                }

                // Output any index with that color
                for (int i = 0; i < d; i++)
                {
                    int col = (s[i] == 'r' ? 0 : s[i] == 'g' ? 1
                                                             : 2);
                    if (col == target)
                    {
                        cout << (i + 1) << "\n";
                        break;
                    }
                }
            }
        }
    }
}