#include <bits/stdc++.h>
using namespace std;
class Solution {
public://b
    int fact(char ch){
        int n = ch - '0';
        int ans = 1;
        for(int i = 1; i <= n; i++){
            ans *= i;
        }
        return ans;
    }
    bool isDigitorialPermutation(int n) {
        string s = to_string(n);
        sort(s.begin(), s.end());

        int sum = 0;
        for(auto & i : s){
            sum += fact(i);
        }

        string ss = to_string(sum);
        sort(ss.begin(), ss.end());

        return ss == s;

    }
};