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



//2nd approach
class Solution {
    long long solve(long long n, int op)
    {
        if (n == 1)
            return 1;
        if (op == 0)
            return solve((n + 1) / 2, 1) * 2 - 1;
        if (n % 2)
            return solve((n + 1) / 2, 0) * 2 - 1;
        return solve(n / 2, 0) * 2;
    }
public:
    long long lastInteger(long long n)
    {
        return solve(n, 0);
    }
};