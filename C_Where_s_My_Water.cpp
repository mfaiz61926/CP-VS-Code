#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        ll h;
        cin >> n >> h;

        vector<ll> a(n+2), pref(n+2);

        for(int i=1;i<=n;i++) cin>>a[i];

        for(int i=1;i<=n;i++)
            pref[i]=pref[i-1]+a[i];

        vector<ll> bestL(n+2), bestR(n+2);

        for(int L=1;L<=n;L++){
            ll mx=0;
            for(int R=L;R<=n;R++){
                mx=max(mx,a[R]);

                ll left=(L>1?a[L-1]:h);
                ll right=(R<n?a[R+1]:h);

                ll y=min({h,left,right});

                if(mx>=y) break;

                ll sum=pref[R]-pref[L-1];
                ll val=(R-L+1)*y-sum;

                bestL[R]=max(bestL[R],val);
                bestR[L]=max(bestR[L],val);
            }
        }

        for(int i=1;i<=n;i++)
            bestL[i]=max(bestL[i],bestL[i-1]);

        for(int i=n;i>=1;i--)
            bestR[i]=max(bestR[i],bestR[i+1]);

        ll ans=0;

        for(int i=0;i<=n;i++)
            ans=max(ans,bestL[i]+bestR[i+1]);

        cout<<ans<<"\n";
    }
}