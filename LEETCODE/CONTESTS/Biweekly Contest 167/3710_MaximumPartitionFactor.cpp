#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool dfs(int node , int col , vector<int>&color, vector<vector<int>>&adj){
        color[node] = col;
        for(auto &it : adj[node]){
            if(color[it] == -1){
                if(dfs(it, !col, color, adj) == false) return false;
            }
            else if (color[it] == col) return false;
        }
        return true;
    }
    bool is_bipartite(vector<vector<int>>&mn_dis, int mid){
        int n = mn_dis.size();
        vector<vector<int>>adj(n);

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(mn_dis[i][j] < mid){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<int>color(n, -1);
        for(int i = 0; i < n; i++){
            if(color[i] == -1){
                if(dfs(i, 0, color, adj) == false) return false;
            }
        }
        return true;
    }
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        if(n<=2) return 0;
        vector<vector<int>>mn_dis(n, vector<int>(n,0));
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                mn_dis[i][j] = mn_dis[j][i] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            }
        }
        int low = 0;
        int high = 1e9;
        int ans = 0;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(is_bipartite(mn_dis, mid)){
                ans = mid;
                low = mid + 1;
            }else high = mid - 1;
        }
        return ans;
    }
};