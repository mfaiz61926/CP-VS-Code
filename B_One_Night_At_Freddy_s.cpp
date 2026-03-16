#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        long long n,m,l;
        cin >> n >> m >> l;

        vector<long long>a(n);
        for(auto &x:a) cin>>x;

        long long lo=0,hi=l,ans=l;

        auto ok=[&](long long x){
            long long need=0;
            long long slots=0;

            for(int i=n-1;i>=0;i--){
                need += max(0LL, l - a[i] - x);
                slots = min(slots+1, m);

                if(need > slots * x)
                    return false;
            }

            return true;
        };

        while(lo<=hi){
            long long mid=(lo+hi)/2;

            if(ok(mid)){
                ans=mid;
                hi=mid-1;
            }
            else lo=mid+1;
        }

        cout<<ans<<"\n";
    }
}