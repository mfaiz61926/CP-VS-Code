#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    map<pair<int, double>, int>mp;
    int solve(int i, vector<int>&nums, double x, double val){
        if(i == nums.size()){
            return fabs(val - x) < 1e-9;
        }

        if(mp.find({i, val}) != mp.end()) return mp[{i, val}];

        int m = solve(i + 1, nums, x, 1.0 *nums[i]*val);
        int d = solve(i + 1, nums, x, val / (nums[i] * 1.0));
        int l = solve(i + 1, nums, x, val);

        return mp[{i, val}] = m + d + l;
    }
    int countSequences(vector<int>& nums, long long k) {
        int n = nums.size();
        mp.clear();
        double x = 1.0 * k;
        double val = 1;
        return  solve(0, nums, x, val);
        
    }
};