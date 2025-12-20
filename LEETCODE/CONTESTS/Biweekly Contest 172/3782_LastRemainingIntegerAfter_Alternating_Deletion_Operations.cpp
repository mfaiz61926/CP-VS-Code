#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long f(long long x){
        if(x == 1) return 1;
        long long d = (x + 1)/2;
        long long p = 2*d + 1 - 2 * f(d);
        return p;
    }
    long long lastInteger(long long n) {
        if(n <3) return 1;
        return f(n);
    }
};