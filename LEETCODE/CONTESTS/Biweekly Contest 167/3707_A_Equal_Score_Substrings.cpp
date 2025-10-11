#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool scoreBalance(string s) {
        int n = s.size();
        vector<int>pre(n,0);
        int sum = 0;
        for(int i = 0; i < n; i++){
            int x = s[i] - 'a' + 1;
            sum +=x ;
            if(i>0) pre[i] = pre[i - 1] + x;
            else pre[0] = x;
        }

        for(int i = 0; i < n; i++){
            if(pre[i] == (sum - pre[i])) return true;
        }
        return false;
    }
};