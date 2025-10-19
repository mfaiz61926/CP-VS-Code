#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n=0){init(n);}
    void init(int n){
        p.resize(n);
        sz.assign(n,1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a;
        sz[a]+=sz[b];
        return true;
    }
};

struct Edge {
    long long w;
    int u, v;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    for(int tc=1; tc<=T; ++tc){
        int N; 
        cin >> N;
        vector<long long> A(N+1);
        for(int i=1;i<=N;++i) cin >> A[i];

        vector<Edge> edges;
        edges.reserve(2LL*N);
       
        for(int i=1;i<=N;++i){
            edges.push_back({A[i], 0, i});
        }
        
        for(int i=1;i<N;++i){
            edges.push_back({llabs(A[i]-A[i+1]), i, i+1});
        }

        sort(edges.begin(), edges.end());
        DSU dsu(N+1);
        long long ans = 0;
        int comps = N+1; 
        for(const auto& e : edges){
            if(dsu.unite(e.u, e.v)){
                ans = e.w;
                comps--;
                if(comps == 1){
                   break;
                } 
            }
        }
        cout <<"Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}
