#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if(!(cin>>T)) return 0;
    for(int tc=1;tc<=T;++tc){
        int N,M;
        cin>>N>>M;
        vector<int>A(N);
        for(int i=0;i<N;++i) cin>>A[i];
        vector<int>B(M);
        for(int i=0;i<M;++i) cin>>B[i];
        sort(A.begin(),A.end(),greater<int>());
        vector<int> groups;
        for(int i=0;i<N;){
            int j=i;
            while(j<N && A[j]==A[i]) ++j;
            groups.push_back(j-i);
            i=j;
        }
        sort(B.begin(),B.end());
        vector<ll> prefB(M+1,0);
        for(int i=0;i<M;++i) prefB[i+1]=prefB[i]+B[i];
        ll best=0;
        ll Ck=0;
        ll sum_ct_t=0;
        int g = groups.size();
        for(int k=1;k<=g;++k){
            int c = groups[k-1];
            Ck += c;
            sum_ct_t += (ll)c * k;
            if(k > M) continue;
            ll Umin = (ll)(k+1)*Ck - sum_ct_t;
            int cnt_le = upper_bound(B.begin(),B.end(),(int)Ck) - B.begin();
            ll S_C = prefB[cnt_le] + (ll)(M - cnt_le) * Ck;
            if(Umin <= S_C) best = max(best, Ck);
        }
        cout<<"Case #"<<tc<<": "<<best<<"\n";
    }
    return 0;
}
