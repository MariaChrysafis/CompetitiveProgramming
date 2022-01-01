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

using namespace std;

typedef int64_t ll;
ll binPow (ll x, ll y) {
    if (y == 0) return 1;
    return binPow(x, y - 1) * x;
}
vector<ll> sieve (const int MAXN) {
    vector<bool> isPrime;
    isPrime.assign(MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    vector<ll> primes;
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}
vector<ll> primes;
int factor (ll x) {
    int ans = 0;
    for (int i = 0; i < primes.size(); i++) {
        if (x % primes[i] == 0) {
            ans += (1 << i);
        }
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    primes = sieve(73);
    map<ll,int> primes_considered;
    ll A, B;
    cin >> A >> B;
    for (ll i = A; i <= B; i++) {
        ll cur = i;
        for (int j: primes) {
            while (cur % j == 0) {
                cur /= j;
                primes_considered[j]++;
            }
        }
        primes_considered[cur]++;
    }
    primes_considered[1] = 0;
    primes.clear();
    for (auto& p: primes_considered) {
        if (p.second >= 2) {
            primes.push_back(p.first);
        }
    }
    vector<int> dp;
    dp.assign((1 << primes.size()), 0);
    int cnt = 0;
    dp[0] = 1;
    for (ll j = A; j <= B; j++) {
        int f = factor(j);
        for (int i = 1; i < (1 << primes.size()); i++) {
            if (f == 0) {
                continue;
            }
            if (i - f == (i ^ f)) {
                dp[i] += dp[i - f] ;
            }
        }
    }
    for (ll j = A; j <= B; j++) {
        cnt += (factor(j) == 0);
    }
    ll ans = 0;
    for (int i = 0; i < dp.size(); i++) {
        ans += dp[i];
    }
    cout << ans * binPow(2, cnt) << '\n';
}
