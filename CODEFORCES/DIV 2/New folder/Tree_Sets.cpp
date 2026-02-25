#include <bits/stdc++.h>
using namespace std;
const int M = 998244353;

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<vector<int>> g(n+1);
        for(int i=0;i<n-1;i++){
            int u,v; cin>>u>>v;
            g[u].push_back(v); g[v].push_back(u);
        }
        vector<int> s(n+1,1),p(n+1,0),o;
        vector<bool> vis(n+1,false);
        stack<pair<int,int>> st;
        st.push({1,0});
        while(!st.empty()){
            auto it=st.top(); st.pop();
            int v = it.first;
            int q = it.second;
            if(vis[v]) continue;
            vis[v]=true; p[v]=q; o.push_back(v);
            for(int nb:g[v]) if(nb!=q) st.push({nb,v});
        }
        for(int i=n-1;i>=0;i--) if(p[o[i]]) s[p[o[i]]]+=s[o[i]];
        long long r=0,d=0;
        for(int v=1;v<=n;v++){
            long long pr=1;
            for(int nb:g[v]) pr=pr*((nb==p[v]?n-s[v]:s[nb])+1)%M;
            r=(r+2*pr-1+M)%M;
            if(v>1) d=(d+(long long)s[v]*(n-s[v]))%M;
        }
        cout<<(r-(long long)n*(n-1)%M-d+2LL*M)%M<<"\n";
    }
}