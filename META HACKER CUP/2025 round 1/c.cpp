#include <bits/stdc++.h>
using namespace std;
typedef long long int64;
const int64 MOD = 998244353;

int K;
struct State { uint32_t mask; uint8_t r; };
vector<State> states;
vector< array<int,10> > trans;
vector<int> masklist[26]; 
vector<int64> preL;

inline uint64_t key(uint32_t m, uint8_t r){
    return (uint64_t(m) << 5) | r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; 
    cin >> T;

    vector<vector<int>> delta(26, vector<int>(10));
    for(int k=2;k<=25;k++)
        for(int d=0;d<=9;d++)
            delta[k][d] = d % k;

    while(T--){
        string Ls, Rs;
        cin >> Ls >> Rs >> K;

        for(int i=0;i<=K;i++) masklist[i].clear();

        states.clear();
        states.push_back({1u<<0,0});
        vector<uint64_t> keys;
        keys.push_back(key(1u<<0,0));

        for(int i=0;i<(int)states.size();i++){
            uint32_t m=states[i].mask;
            uint8_t r=states[i].r;
            for(int d=0;d<=9;d++){
                int nr=(r+delta[K][d])%K;
                if((m>>nr)&1u) continue;
                uint32_t nm=m|(1u<<nr);
                uint64_t k=key(nm,nr);
                auto it=lower_bound(keys.begin(),keys.end(),k);
                if(it==keys.end()||*it!=k){
                    keys.insert(it,k);
                    states.push_back({nm,(uint8_t)nr});
                }
            }
        }

        int S=states.size();
        for(int i=0;i<=K;i++) masklist[i].clear();

        vector<int> posmap(S);
        for(int i=0;i<S;i++){
            int bc=__builtin_popcount(states[i].mask);
            masklist[bc].push_back(i);
        }

        trans.assign(S, array<int,10>());
        for(int i=0;i<S;i++){
            uint32_t m=states[i].mask;
            uint8_t r=states[i].r;
            for(int d=0;d<=9;d++){
                int nr=(r+delta[K][d])%K;
                if((m>>nr)&1u){ trans[i][d]=-1; continue; }
                uint32_t nm=m|(1u<<nr);
                uint64_t k=key(nm,nr);
                int id = lower_bound(keys.begin(),keys.end(),k)-keys.begin();
                trans[i][d]=id;
            }
        }

        preL.assign(K,0);
        vector<int64> dp(S,0), nxt(S,0);
        dp[0]=1;

        for(int len=1;len<=K-1;len++){
            for(int i=0;i<S;i++) nxt[i]=0;
            for(int idx : masklist[len-1]){
                int64 val = dp[idx];
                if(val==0) continue;
                for(int d=0;d<=9;d++){
                    if(len==1 && d==0) continue;
                    int j = trans[idx][d];
                    if(j<0) continue;
                    nxt[j] = (nxt[j] + val) % MOD;
                }
            }
            int64 sum = 0;
            for(int i=0;i<S;i++) sum = (sum + nxt[i]) % MOD;
            preL[len] = sum;
            dp.swap(nxt);
        }

        function<int64(const string&)> count_leq = [&](const string &Sstr){
            int n=Sstr.size();
            if(n==0) return 0LL;
            if(n>=K){
                int64 s=0;
                for(int i=1;i<=K-1;i++) s=(s+preL[i])%MOD;
                return s;
            }
            int64 ans=0;
            for(int i=1;i<n;i++) ans=(ans+preL[i])%MOD;

            static int64 memo[21][26][200000];
            static bool vis [21][26][200000];
            memset(vis,0,sizeof(vis));

            function<int64(int,int)> dfs=[&](int pos,int sid)->int64{
                if(pos==n) return 1;
                if(vis[pos][sid/200000][sid%200000]) 
                    return memo[pos][sid/200000][sid%200000];

                vis[pos][sid/200000][sid%200000]=true;
                int64& res = memo[pos][sid/200000][sid%200000];
                res=0;

                int limit = Sstr[pos]-'0';
                for(int d=0;d<=limit;d++){
                    if(pos==0 && d==0) continue;
                    int j = trans[sid][d];
                    if(j<0) continue;
                    if(d==limit) res=(res+dfs(pos+1,j))%MOD;
                    else{
                        int need = pos+1;
                        for(size_t x=0;x<masklist[need].size();x++){
                            res=(res+dp[masklist[need][x]])%MOD;
                        }
                    }
                }
                return res;
            };

            return (ans + dfs(0,0)) % MOD;
        };

        auto dec1=[&](string s){
            int i=s.size()-1;
            while(i>=0 && s[i]=='0'){ s[i]='9'; i--; }
            if(i<0) return string("");
            s[i]--;
            if(s.size()>1 && s[0]=='0'){
                size_t p=s.find_first_not_of('0');
                if(p==string::npos) return string("0");
                s=s.substr(p);
            }
            return s;
        };

        auto modstr=[&](const string&s){
            int64 v=0;
            for(char c:s) v=(v*10+(c-'0'))%MOD;
            return v;
        };

        int64 nr = count_leq(Rs);
        string Lm = dec1(Ls);
        int64 nl = Lm.empty()?0:count_leq(Lm);

        int64 tot = (modstr(Rs) - (Lm.empty()?0:modstr(Lm)) + MOD) % MOD;
        int64 nonw = (nr - nl + MOD) % MOD;
        int64 ans = (tot - nonw + MOD) % MOD;

        static int cas=1;
        cout<<"Case #"<<cas++<<": "<<ans<<"\n";
    }

    return 0;
}
