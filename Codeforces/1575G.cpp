#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 1;
vector<ll> phi;
vector<vector<ll>> factors(MAX);

ll gcd (ll a, ll b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}

void sieve () {
    phi.resize(MAX);
    for (int i = 0; i < MAX; i++) {
        phi[i] = i;
    }
    for (int i = 2; i < MAX; i++) {
        if (phi[i] == i) {
            phi[i]--;
            for (int j = 2 * i; j < MAX; j += i) {
                phi[j] = phi[j]/i * (i - 1);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            factors[j].push_back(i);
        }
    }
    sieve();
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll res = 0;
    vector<ll> cnt;
    cnt.assign(MAX, 0);
    for (int x = 1; x <= n; x++) {
        vector<int> to_rem;
        for (int i = x; i <= n; i += x) {
            for (int j: factors[a[i]]) {
                if (!cnt[j]) {
                    to_rem.push_back(j);
                }
                cnt[j]++;
            }
        }
        for (int j: to_rem) {
            res += (cnt[j] * cnt[j] * phi[x] * phi[j]) % MOD;
            res %= MOD;
            cnt[j] = 0;
        }
    }
    cout << res << '\n';
}
