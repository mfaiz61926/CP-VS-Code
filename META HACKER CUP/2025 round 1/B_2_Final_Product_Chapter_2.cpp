/******************************************************************************

                              بسم الله الرحمان الرحيم
author:mfaiz_1

*******************************************************************************/
#include "bits/stdc++.h"
#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define fr_3(i,n) for(int i=0;i<(n);i++)
#define fb_3(i,a,n) for(int i=(a);i<=(n);i++)
#define nl cout<<"\n"
#define dbg(var) cout<<#var<<"="<<var<<" "
#define all_3(v) v.begin(),v.end()
#define srt_3(v) sort(v.begin(),v.end())
#define mxe_3(v) *max_element(v.begin(),v.end())
#define mne_3(v) *min_element(v.begin(),v.end())
#define unq_3(v) v.resize(distance(v.begin(),unique(v.begin(),v.end())))
#define bin(x,y) bitset<y>(x)
using namespace std;

const int MOD = 1000000007;

// ---------------- Modular Ops ----------------
int mod_pow(int a,int e){
    int r=1;
    while(e>0){
        if(e&1) r=(r*a)%MOD;
        a=(a*a)%MOD;
        e>>=1;
    }
    return r;
}
int mod_inv(int x){ return mod_pow(x,MOD-2); }

int nCr_mod(int n,int r){
    if(r<0 || r>n) return 0;
    int res=1;
    fb_3(i,1,r){
        res = (res*((n-i+1)%MOD))%MOD;
        res = (res*mod_inv(i))%MOD;
    }
    return res;
}

// ---------------- MillerRabin + PollardRho (for robust factoring) ----------------
using u128 = unsigned __int128;
int64_t mul_mod64(int64_t a, int64_t b, int64_t mod) {
    u128 res = (u128)a * (u128)b;
    res %= (u128)mod;
    return (int64_t)res;
}
int64_t pow_mod64(int64_t a, int64_t d, int64_t mod) {
    int64_t r = 1;
    while (d) {
        if (d & 1) r = mul_mod64(r, a, mod);
        a = mul_mod64(a, a, mod);
        d >>= 1;
    }
    return r;
}
bool isPrime64(int64_t n) {
    if (n < 2) return false;
    for (int64_t p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n%p==0) return n==p;
    }
    int64_t d = n-1, s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    // bases good for 64-bit
    for (int64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        int64_t x = pow_mod64(a % n, d, n);
        if (x==1 || x==n-1) continue;
        bool comp = true;
        for (int r=1; r<(int)s; ++r) {
            x = mul_mod64(x, x, n);
            if (x==n-1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}
std::mt19937_64 rng((uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count());
int64_t pollards_rho_once(int64_t n) {
    if (n%2==0) return 2;
    if (n%3==0) return 3;
    int64_t c = std::uniform_int_distribution<int64_t>(1, n-1)(rng);
    int64_t x = std::uniform_int_distribution<int64_t>(2, n-2)(rng);
    int64_t y = x;
    int64_t d = 1;
    auto f = [&](int64_t v){ return (mul_mod64(v, v, n) + c) % n; };
    while (d==1) {
        x = f(x);
        y = f(f(y));
        d = std::__gcd((int64_t)llabs(x - y), n);
        if (d==n) return pollards_rho_once(n);
    }
    return d;
}
void factor_rec(int64_t n, vector<int64_t> &out) {
    if (n==1) return;
    if (isPrime64(n)) { out.push_back(n); return; }
    int64_t d = pollards_rho_once(n);
    factor_rec(d, out);
    factor_rec(n/d, out);
}
vector<pair<int,int>> get_factors_pollard(long long n){
    vector<int64_t> primes;
    if (n<=1) return vector<pair<int,int>>();
    factor_rec(n, primes);
    sort(primes.begin(), primes.end());
    vector<pair<int,int>> res;
    for (size_t i=0;i<primes.size();){
        size_t j=i;
        while (j<primes.size() && primes[j]==primes[i]) ++j;
        res.push_back(make_pair((int)primes[i], (int)(j-i)));
        i=j;
    }
    return res;
}

// ---------------- Divisors (iterative, overflow-safe) ----------------
vector<int> make_divs_safe(const vector<pair<int,int>>& fac){
    vector<int> divs;
    divs.push_back(1);
    for(size_t idx=0; idx<fac.size(); ++idx){
        int p = fac[idx].first;
        int e = fac[idx].second;
        vector<int> tmp;
        // use __int128 for mul checks
        for (int exp = 0; exp <= e; ++exp){
            __int128 mult = 1;
            for (int i=0;i<exp;i++) mult *= p;
            for (size_t k=0;k<divs.size();++k){
                __int128 val = (__int128)divs[k] * mult;
                if (val > ( (__int128)LLONG_MAX )) continue;
                tmp.push_back((int)val);
            }
        }
        divs.swap(tmp);
    }
    return divs;
}

// ---------------- Combinatorial Ways (with memo on n,N pair) ----------------
struct PairHash {
    size_t operator()(const pair<long long,long long>&p) const noexcept {
        // 64-bit mix
        uint64_t x = (uint64_t)p.first;
        uint64_t y = (uint64_t)p.second;
        x ^= x >> 33;
        x *= 0xff51afd7ed558ccdULL;
        x ^= x >> 33;
        x += (y ^ (y << 11));
        return (size_t)x;
    }
};

unordered_map<pair<long long,long long>, long long, PairHash> memo_pair;

int calc_ways_memo(int n,int N){
    pair<long long,long long> key = make_pair((long long)n,(long long)N);
    auto it = memo_pair.find(key);
    if (it!=memo_pair.end()) return it->second;
    vector<pair<int,int>> fac = get_factors_pollard(n);
    long long ans = 1;
    for(size_t i=0;i<fac.size();++i){
        int e = fac[i].second;
        ans = (ans * nCr_mod(e + N - 1, N - 1)) % MOD;
    }
    memo_pair[key] = ans;
    return ans;
}

// ---------------- Solve Function ----------------
void funny_3(int tc){
    int N,A,B;
    cin>>N>>A>>B;

    vector<pair<int,int>> fac = get_factors_pollard(B);
    vector<int> divs = make_divs_safe(fac);
    long long ans = 0;
    memo_pair.clear();

    for(size_t i=0;i<divs.size();++i){
        int p = divs[i];
        if (p <= A && B % p == 0){
            int part1 = calc_ways_memo(p, N);
            int part2 = calc_ways_memo(B / p, N);
            ans = (ans + ( (long long)part1 * part2 ) % MOD) % MOD;
        }
    }
    cout<<"Case #"<<tc<<": "<<ans%MOD<<"\n";
}

// ---------------- Main ----------------
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t_c_3 = 1;
    if(!(cin>>t_c_3)) return 0;
    fb_3(i,1,t_c_3){
        funny_3(i);
    }
    return 0;
}
