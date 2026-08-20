#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int n, q;
vector<int> comp;
vector<ull> hval;
int V;

struct FenwickCnt {
    int n;
    vector<int> fn;
    void init(int n_){ n=n_; fn.assign(n+1,0); }
    void add(int x,int val){ x++; while(x<=n){ fn[x]+=val; x+=x&(-x);} }
    int sum(int x){ if(x<0) return 0; x++; int r=0; while(x>0){ r+=fn[x]; x-=x&(-x);} return r; }
};

struct FenwickHash {
    int n;
    vector<ull> fn;
    void init(int n_){ n=n_; fn.assign(n+1,0); }
    void add(int x, ull val){ x++; while(x<=n){ fn[x]+=val; x+=x&(-x);} }
    ull sum(int x){ if(x<0) return 0; x++; ull r=0; while(x>0){ r+=fn[x]; x-=x&(-x);} return r; }
};

FenwickCnt FC;
FenwickHash FH;
FenwickHash FOU;

int getIdx(int v){
    return (int)(lower_bound(comp.begin(), comp.end(), v) - comp.begin());
}

int findKth(int k){
    int pos = 0;
    int remaining = k;
    int LOG = 1;
    while((1<<LOG) <= V) LOG++;
    for(int j = LOG; j >= 0; j--){
        int nxt = pos + (1<<j);
        if(nxt <= V && FC.fn[nxt] < remaining){
            pos = nxt;
            remaining -= FC.fn[nxt];
        }
    }
    return pos;
}

ull sortedPrefixHash(int p){
    if(p==0) return 0ULL;
    if(p==n) return FH.sum(V-1);
    int v = findKth(p);
    int before = FC.sum(v-1);
    int needed = p - before;
    ull res = FH.sum(v-1) + (ull)needed * hval[v];
    return res;
}

ull origPrefixHash(int p){
    if(p==0) return 0ULL;
    return FOU.sum(p-1);
}

bool isBad(int p){
    return origPrefixHash(p) != sortedPrefixHash(p);
}

int firstBadPrefix(){
    function<int(int,int)> solve = [&](int l, int r) -> int {
        if(l+1 == r) return isBad(l+1) ? (l+1) : -1;
        int mid = (l+r)/2;
        int res = solve(l, mid);
        if(res != -1) return res;
        return solve(mid, r);
    };
    int ans = solve(0, n);
    return ans == -1 ? n : ans;
}

int computeF(){
    int p = firstBadPrefix();
    if(p >= n) return 0;
    int step = 1;
    while(step < p) step <<= 1;
    return step;
}

void m_conq(){
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x: a) cin >> x;

    vector<pair<int,int>> updates(q);
    vector<int> allvals(a);
    for(auto &pr : updates){
        cin >> pr.first >> pr.second;
        allvals.push_back(pr.second);
    }

    comp = allvals;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    V = (int)comp.size();

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    hval.assign(V, 0);
    for(int i=0;i<V;i++) hval[i] = rng();

    FC.init(V);
    FH.init(V);
    FOU.init(n);

    vector<int> cur(a);
    for(int i=0;i<n;i++){
        int idx = getIdx(cur[i]);
        FC.add(idx, 1);
        FH.add(idx, hval[idx]);
        FOU.add(i, hval[idx]);
    }

    cout << computeF() << "\n";

    for(auto &pr : updates){
        int i = pr.first, x = pr.second;
        int oldIdx = getIdx(cur[i]);
        int newIdx = getIdx(x);

        FC.add(oldIdx, -1);
        FH.add(oldIdx, (ull)0 - hval[oldIdx]);
        FOU.add(i, (ull)0 - hval[oldIdx]);

        cur[i] = x;

        FC.add(newIdx, 1);
        FH.add(newIdx, hval[newIdx]);
        FOU.add(i, hval[newIdx]);

        cout << computeF() << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while(t--){
        m_conq();
    }
    return 0;
}