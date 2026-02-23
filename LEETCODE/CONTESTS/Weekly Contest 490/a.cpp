#include <bits/stdc++.h>
using namespace std;
class Solution {
public: // prob a
    int scoreDifference(vector<int>& nums) {
        int tot_a = 0, tot_b = 0;
        int a = 1, b = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % 2 == 1){
                swap(a, b);
            }
            if((i + 1) % 6 == 0) swap(a, b);
            if(a) tot_a += nums[i];
            else tot_b += nums[i];
        }

        return tot_a - tot_b;
    }
};