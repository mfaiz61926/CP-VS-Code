#include <bits/stdc++.h>
using namespace std;

inline unsigned long long C2(unsigned long long c){
    if(c<2) return 0;
    return (c&1?c*((c-1)>>1):((c>>1)*(c-1)));
}

inline unsigned long long C3(unsigned long long c){
    if(c<3) return 0;
    unsigned long long a=c,b=c-1,d=c-2;
    if((a&1)==0) a>>=1;
    else if((b&1)==0) b>>=1;
    else d>>=1;
    if(a%3==0) a/=3;
    else if(b%3==0) b/=3;
    else d/=3;
    return a*b*d;
}

inline unsigned long long Cn3(unsigned long long n){
    unsigned long long a=n,b=n+1,c=n+2;
    if((a&1)==0) a>>=1;
    else if((b&1)==0) b>>=1;
    else c>>=1;
    if(a%3==0) a/=3;
    else if(b%3==0) b/=3;
    else c/=3;
    return a*b*c;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; if(!(cin>>t)) return 0;
    for(int tc=1;tc<=t;++tc){
        int n; cin>>n;
        vector<uint32_t> v(n+1);
        for(int i=1;i<=n;++i) cin>>v[i];
        unordered_map<uint32_t,unsigned> f;
        f.reserve(min(2LL*n+5,(1LL<<26)));
        uint32_t x=0; ++f[x];
        for(int i=1;i<=n;++i) x^=v[i],++f[x];
        unsigned long long tot=Cn3(n),s2=0,s3=0;
        for(auto &p:f){
            unsigned long long c=p.second;
            s2+=C2(c);
            s3+=C3(c);
        }
        cout<<"Case #"<<tc<<": "<<tot-s2-s3<<"\n";
    }
}
