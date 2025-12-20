#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int mx = 0;
    vector<int>f,g,h;
    int maximumSum(vector<int>& nums) {
        for(int i =0; i < nums.size(); i++){
            if(nums[i] % 3 == 0)f.push_back(nums[i]);
            else if(nums[i] % 3 == 1) g.push_back(nums[i]);
            else h.push_back(nums[i]);
        }
        sort(h.rbegin(), h.rend());
        sort(g.rbegin(), g.rend());
        sort(f.rbegin(), f.rend());

        
        if(f.size() >= 3){
            mx = max(mx, f[0] + f[1] + f[2]);
        }
        if(g.size() >= 3){
            mx = max(mx, g[0] + g[1] + g[2]);
        }
        if(h.size() >= 3){
            mx = max(mx, h[0] + h[1] + h[2]);
        }
        if(!f.empty() && !g.empty() && !h.empty()){
            mx = max(mx, f[0] + g[0] + h[0]);
        }

        return mx;
    }
};