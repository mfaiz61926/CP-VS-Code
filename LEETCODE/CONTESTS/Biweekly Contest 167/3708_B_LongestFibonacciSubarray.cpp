#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        if(n<=2) return n;
        int cnt = 2;
        int mx = 2;
        for(int i = 2; i < n; i++){
            if(nums[i]== nums[i-1] + nums[i - 2]){
                cnt++;
            }
            else cnt = 2;
            mx = max(mx , cnt);
        }
        return mx;
    }
};