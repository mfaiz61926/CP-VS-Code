
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const ull ULL_NEG_INF = 0;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    for(int tc=1; tc<=T; ++tc){
        int N;
        ull M;
        cin >> N >> M;
        vector<ull> A(N+1);
        for(int i=1;i<=N;++i) cin >> A[i];

       
        vector<ull> pref(N+1,0);
        for(int k=1;k<=N;++k) pref[k] = pref[k-1] + A[k];

        vector<int> items;
        for(int k=1;k<=N;++k) {
            if(pref[k] == pref[k-1]) continue; 
            items.push_back(k);
        }
        if(items.empty()){
            
            cout << "Case #" << tc << ": ";
            if(M==0){
                cout << 0 << "\n";
                for(int i=0;i<N;i++){ if(i) cout << ' '; cout << 0; }
                cout << "\n";
            } else {
               
                cout << "0\n";
                for(int i=0;i<N;i++){ if(i) cout << ' '; cout << 0; }
                cout << "\n";
            }
            continue;
        }

    
        int bestK = items[0];
        long double bestRatio = (long double)pref[bestK] / (long double)bestK;
        for(int k : items){
            long double r = (long double)pref[k] / (long double)k;
            if(r > bestRatio + 1e-18L){
                bestRatio = r;
                bestK = k;
            }
        }

      
        int LIMIT = 200000;
      
        if((long long)N * 200 > LIMIT) {
            LIMIT = min(500000, max(200000, N * 200)); // tweak based on N
        }

        if(LIMIT < bestK) LIMIT = bestK;

       
        vector<ull> dp(LIMIT+1, 0ULL);
        for(int k : items){
            int cost = k;
            ull val = pref[k];
            if(cost > LIMIT) continue;
            for(int c = cost; c <= LIMIT; ++c){
                ull cand = dp[c - cost] + val;
                if(cand > dp[c]) dp[c] = cand;
            }
        }
        for(int c=1;c<=LIMIT;++c) if(dp[c-1] > dp[c]) dp[c] = dp[c-1];

        auto feasible = [&](unsigned long long B)->bool{
            if(B <= (ull)LIMIT){
                return dp[(int)B] >= M;
            } else {
                int k = bestK;
                
                unsigned long long diff = B - (unsigned long long)LIMIT;
                unsigned long long q = (diff + (unsigned long long)k - 1ULL) / (unsigned long long)k;
                unsigned long long usedCost = q * (unsigned long long)k;
                if(usedCost > B) return false; 
                unsigned long long remain = B - usedCost;
                if(remain > (unsigned long long)LIMIT) return false; 
                unsigned long long val = q * pref[k];
                if(val >= M) return true;
                ull remval = dp[(int)remain];
                unsigned long long total = val + remval;
                return total >= M;
            }
        };

        unsigned long long lo = 0, hi = M; // hi inclusive
        while(lo < hi){
            unsigned long long mid = lo + (hi - lo) / 2;
            if(feasible(mid)) hi = mid;
            else lo = mid + 1;
        }
        unsigned long long Bmin = lo;

       
        vector<unsigned long long> d(N+1, 0ULL);

        unsigned long long remainingB = Bmin;
        if(Bmin > (unsigned long long)LIMIT){
            int k = bestK;
            unsigned long long diff = Bmin - (unsigned long long)LIMIT;
            unsigned long long q = (diff + (unsigned long long)k - 1ULL) / (unsigned long long)k;
            d[k] += q;
            unsigned long long usedCost = q * (unsigned long long)k;
            remainingB -= usedCost;
        }

       
        int R = (int)min<unsigned long long>(remainingB, (unsigned long long)LIMIT);
        vector<ull> dp2(R+1, 0ULL);
        vector<int> parent(R+1, -1); // which k used last to reach dp2[c]
        for(int c=0;c<=R;++c){ dp2[c] = 0; parent[c] = -1; }
        for(int k : items){
            int cost = k;
            ull val = pref[k];
            if(cost > R) continue;
            for(int c = cost; c <= R; ++c){
                ull cand = dp2[c - cost] + val;
                if(cand > dp2[c]){
                    dp2[c] = cand;
                    parent[c] = k;
                }
            }
        }
        for(int c=1;c<=R;++c){
            if(dp2[c-1] > dp2[c]){
                dp2[c] = dp2[c-1];
                parent[c] = -2; // means copy from c-1 (no new item)
            }
        }

        int target = R;
        ull alreadyVal = 0;
        for(int k=1;k<=N;++k) if(d[k]) alreadyVal += d[k] * pref[k];

        // Reconstruct counts from parent[] for capacity 'target' (we may need to backtrack)
        int c = target;
        // because parent[c] == -2 indicates dp2[c] was copied from dp2[c-1], we should move left until we find actual item choices.
        while(c > 0){
            if(parent[c] == -1){
                // no item used at this capacity; move left
                c--;
            } else if(parent[c] == -2){
                c--; // copied from previous
            } else {
                int k = parent[c];
                if(k <= 0) break;
                d[k] += 1ULL;
                c -= k;
            }
        }
        unsigned long long usedCost = 0ULL;
        for(int k=1;k<=N;++k) usedCost += d[k] * (unsigned long long)k;
        if(usedCost < remainingB){
            unsigned long long need = remainingB - usedCost;
            int k = bestK;
            unsigned long long q = need / (unsigned long long)k;
            d[k] += q;
            usedCost += q * (unsigned long long)k;
            unsigned long long rem = remainingB - usedCost;
            if(rem > 0){
                int pick = -1;
                for(int kk : items){
                    if((unsigned)kk <= rem){
                        if(pick == -1 || (long double)pref[kk] / (long double)kk > (long double)pref[pick] / (long double)pick) pick = kk;
                    }
                }
                if(pick != -1){
                    d[pick] += 1ULL;
                    usedCost += pick;
                } else {
                    d[bestK] += 1ULL;
                    usedCost += bestK;
                }
            }
        }

        vector<unsigned long long> x(N+2, 0ULL); // 1..N
        unsigned long long running = 0ULL;
        for(int i=N;i>=1;--i){
            running += d[i];
            x[i] = running;
        }

        unsigned long long totalBricks = 0ULL;
        unsigned long long totalValue = 0ULL;
        for(int i=1;i<=N;++i){
            totalBricks += x[i];
            totalValue += x[i] * A[i];
        }
        if(totalValue >= M && totalBricks > Bmin){
            for(int i=N;i>=1 && totalBricks > Bmin; --i){
                while(x[i] > 0 && totalBricks > Bmin){
                    if(i < N && x[i]-1 < x[i+1]) break;
                    x[i] -= 1;
                    totalBricks -= 1;
                    totalValue -= A[i];
                    if(totalValue < M){
                        x[i] += 1;
                        totalBricks += 1;
                        totalValue += A[i];
                        break;
                    }
                }
            }
        }

        if(totalValue < M){
            for(int addRound=0; addRound<2 && totalValue < M; ++addRound){
                for(int k=N;k>=1 && totalValue < M; --k){
                    for(int i=1;i<=k && totalValue < M; ++i){
                        x[i] += 1;
                        totalBricks += 1;
                        totalValue += A[i];
                    }
                }
            }
        }

        cout << "Case #" << tc << ": " << Bmin << "\n";
        for(int i=1;i<=N;++i){
            if(i>1) cout << ' ';
            cout << x[i];
        }
        cout << "\n";
    }
    return 0;
}
