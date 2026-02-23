#include <bits/stdc++.h>
using namespace std;
class Solution {
public: // c
    string maximumXor(string s, string t) {
        string ans = "";
        unordered_map<char, int>mp;
        for(auto & c : t){
            mp[c]++;
        }
        for(int i = 0; i < s.size(); i++){
            char c = s[i];
            char f = '0';
            if(c == '0')f = '1';
            else f = '0';
            if(mp[f] > 0){
                mp[f]--;
                ans += '1';
            }
            else ans += '0';
        }
        return ans;
    }
};