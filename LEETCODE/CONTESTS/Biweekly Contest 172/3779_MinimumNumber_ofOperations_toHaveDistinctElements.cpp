#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int>vis;
         unordered_set<int>s;
        bool ok = true;
        for(auto & i : nums){
            if(vis.count(i)){
                ok = false;
                break;
            }
            vis.insert(i);
        }
        if(ok) return 0;

       
        int i = n;
        for(int j = n - 1; j>=0; j--){
            if(s.count(nums[j])){
                i = j+1;
                break;
            }
            s.insert(nums[j]);
        }

        return (i+2) / 3;
    }
};