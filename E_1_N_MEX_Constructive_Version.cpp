#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        vector<int> a(n);
        for(auto &x:a) scanf("%d",&x);
        
        int BN = n+3;
        vector<int> bit(BN+2, 0);
        auto upd=[&](int i, int v){ for(i++;i<(int)bit.size();i+=i&-i) bit[i]+=v; };
        auto qry=[&](int i)->int{ int s=0; for(i++;i>0;i-=i&-i) s+=bit[i]; return s; };
        // count |S ∩ [0..x-1]|, all insertions are in [0..n]
        auto pl=[&](int x)->int{
            if(x<=0) return 0;
            return qry(min(x-1, n+1));
        };
        
        set<int> S;
        int mex_val=0, sz=0;
        bool ok=true;
        vector<int> b(n);
        
        for(int i=0;i<n&&ok;i++){
            int k=n-i;         // k = n-i+1 but 0-indexed so k = n-i
            int ai=a[i];
            if(ai < k-1){ ok=false; break; }    // necessary: ai >= k-1
            if(S.count(ai)){ ok=false; break; }  // ai must not be in S
            
            int cur  = pl(ai);       // |S ∩ [0..ai-1]|
            int need = ai - k + 1;   // required present_less
            int diff = need - cur;
            
            if(diff < 0 || diff > 1){ ok=false; break; }
            
            if(diff == 1){
                // Insert mex_val (guaranteed < ai)
                b[i] = mex_val;
                S.insert(mex_val); upd(mex_val, 1); sz++;
                mex_val++;
                while(S.count(mex_val)) mex_val++;
            } else {
                // diff==0: no new element needed below ai
                if(sz > 0){
                    b[i] = *S.begin(); // repeat existing value
                } else {
                    // S empty only at i=0, meaning ai=n-1
                    b[i] = n;  // pick n (> ai = n-1)
                    S.insert(n); upd(n, 1); sz++;
                }
            }
        }
        
        if(!ok) printf("NO\n");
        else {
            printf("YES\n");
            for(int i=0;i<n;i++) printf("%d%c", b[i], " \n"[i==n-1]);
        }
    }
}