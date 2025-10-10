#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// Legendre v_p(t!) = sum_{j>=1} floor(t / p^j)
static inline int64 vp_fact(int64 t, int p) {
    int64 s = 0;
    for (int64 pp = p; pp <= t; pp *= p) s += t / pp;
    return s;
}

// floor(log_p m): largest e with p^e <= m
static inline int emax_for(int p, int64 m) {
    int e = 0;
    long double pm = (long double)m;
    while (pm >= p) {
        pm /= p;
        ++e;
    }
    return e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 n, m;
        cin >> n >> m;

        // U = min(n, m), primes up to U are the only primes that can affect v_k(n!)>0
        int U = (int)min(n, m);

        // Sieve primes up to U
        vector<int> primes;
        vector<bool> is_composite(U + 1, false);
        for (int i = 2; i <= U; ++i) {
            if (!is_composite[i]) {
                primes.push_back(i);
                if ((int64)i * i <= U)
                    for (int j = i * i; j <= U; j += i) is_composite[j] = true;
            }
        }

        // Precompute v_p(n!) and emax[p] for primes
        const int P = (int)primes.size();
        vector<int64> vpn(P);
        vector<int> emaxp(P);
        for (int i = 0; i < P; ++i) {
            int p = primes[i];
            vpn[i] = vp_fact(n, p);
            emaxp[i] = emax_for(p, m);
        }

        auto zero_possible = [&](int64 x) -> bool {
            // Check if there exists a prime p with vp(x!) < min(vp(n!), emax[p])
            for (int i = 0; i < P; ++i) {
                int p = primes[i];
                if (emaxp[i] == 0) continue;                  // p > m ⇒ no e>=1
                if (vpn[i] == 0) continue;                    // p > n ⇒ v_p(n!)=0
                int64 vpx = vp_fact(x, p);
                int lim = min<int64>(vpn[i], emaxp[i]);
                if (vpx < lim) return true;                   // choose e in (vpx .. lim]
            }
            return false;
        };

        auto fm = [&](int64 x) -> int64 {
            // If 0 achievable, return 0; else minimize floor(vp(x!)/e) over primes and valid e
            if (zero_possible(x)) return 0;
            int64 best = LLONG_MAX;
            for (int i = 0; i < P; ++i) {
                int p = primes[i];
                if (emaxp[i] == 0) continue;
                if (vpn[i] == 0) continue;
                int64 vpx = vp_fact(x, p);
                int64 vpnv = vpn[i];
                // Find largest e in [1..emax] with floor(vpx/e) < floor(vpn/e)
                // Since floors decrease with e, binary search e
                int lo = 1, hi = emaxp[i], ok = 0;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (vpx / mid < vpnv / mid) {
                        ok = mid;
                        lo = mid + 1;
                    } else {
                        hi = mid - 1;
                    }
                }
                if (ok) {
                    best = min(best, vpx / ok);
                }
            }
            // Problem guarantees result < 1e100, and if unreachable (shouldn't), return large
            return best == LLONG_MAX ? (int64)0 : best;
        };

        int64 ans = 0;
        for (int64 x = 1; x <= n - 1; ++x) ans += fm(x);
        cout << ans << '\n';
    }
    return 0;
}
