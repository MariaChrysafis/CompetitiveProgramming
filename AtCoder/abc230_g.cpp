#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>


using namespace std;

typedef int64_t ll;

const int MOD = 998244353;

const int MAXN = 2e5 + 1;

vector<int> spf(MAXN);
void seive(int n) {
    spf[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (int j = 2 * i; j <= n; j += i) {
                spf[j] = i;
            }
        }
    }
}

vector<int> mu;
int mobF(int x) {
    if (mu[x] != -5) {
        return mu[x];
    }
    if (x == 1) {
        return mu[x] = 1;
    } else if (spf[x] == x) {
        return mu[x] = -1;
    } else if ((x / spf[x]) % spf[x]) {
        return mu[x] = mobF(x / spf[x]) * mobF(spf[x]);
    } else {
        return mu[x] = 0;
    }
}
void mobF_to(int n) {
    for (int i = 1; i <= n; i++) {
        mobF(i);
    }
}

ll gcd(ll u, ll v) {
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            swap(u, v);
        }  
        v = v - u;
    } while (v != 0);
    return u << shift;
}

int sq;

ll func1 (vector<int>& v) {
    ll myMax = 0;
    for (int i = 0; i < v.size(); i++) {
        myMax = max(myMax, (ll)v[i]);
    }
    ll f[myMax + 1];
    ll oc[myMax + 1];
    ll o[myMax + 1];
    for (int i = 0; i <= myMax; i++) {
        f[i] = oc[i] = o[i] = 0;
    }
    for (int i: v) {
        o[i]++;
    }
    for (int i = 1; i <= myMax; i++) {
        if (mu[i] == 0) {
            continue;
        }
        for (int j = i; j <= myMax; j += i) {
            oc[i] += o[j];
        }
    }
    ll ans = 0;
    for (int i = 0; i <= myMax; i++) {
        f[i] = oc[i] * (oc[i] + 1)/2;
    }
    for (int j = 1; j <= myMax; j ++) {
        ans += f[j] * mu[j];
    }
    return (ll)v.size() * ((ll)v.size() - 1)/2 + (ll)v.size() - ans;

}

ll func2 (vector<int>& v) {
    ll cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i; j < v.size(); j++) {
            if (gcd(v[i], v[j]) != 1) {
                cntr++;
            }
        }
    }
    return cntr;
}

ll func (vector<int>& v) {
    if (v.size() <= sq) {
        return func2(v);
    }
    return func1(v);
}

void solve() {
    int n;
    cin >> n;
    sq = 200;
    mu.assign(MAXN, -5);
    seive(MAXN + 1), mobF_to(MAXN + 1);
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<ll> f;
    f.assign(p.size() + 1, 0);
    for (int i = 1; i < p.size(); i++) {
        vector<int> cal;
        for (int j = i; j < p.size(); j += i) {
            cal.push_back(p[j]);
        }
        f[i] = func(cal);
    }
    vector<ll> g;
    g.assign(f.size(), 0);
    for (int i = 1; i < g.size(); i++) {
        for (int j = i; j < g.size(); j += i) {
            g[i] += f[j] * mu[j/i];
        }
    }
    ll ans = 0;
    for (int i = 2; i < g.size(); i++) {
        ans += g[i];
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
