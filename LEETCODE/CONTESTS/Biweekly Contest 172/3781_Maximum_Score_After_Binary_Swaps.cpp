#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int n;
    long long ans = 0;
    priority_queue<int, vector<int>,greater<>>pq;
    long long maximumScore(vector<int>& nums, string s) {
       
        for(int i = nums.size() - 1; i >= 0; i--){
            n = nums.size();
            if(s[i] == '1')pq.push(nums[i]);
            else{
                if(!pq.empty() && nums[i] > pq.top()){
                    pq.pop();
                    pq.push(nums[i]);
                }
            }
            
        }
        while(!pq.empty()){
            ans += pq.top();
            pq.pop();
        }

        return ans;
    }
};