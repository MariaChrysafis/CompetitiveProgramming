/*
     * Observations:
     * 1) We can fix a prime and then find the cost if we make the gcd divisible by that prime
     * 2) If a prime occurs frequently, then it's probably a good idea to use it
     * 3) cnt[p] -> the number of elements which are divisible p, or can be made divisible by p using at most 1 operation (1 mod p, 0 mod p, -1 mod p)
     * 4) cnt[p] < cnt[2] in order for us to consider it
*/
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
vector<int> sieve (int N) {
    vector<bool> isPrime;
    isPrime.assign(N + 1, true);
    isPrime[0] = isPrime[1] = false;
    vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}
ll cost (vector<ll> v, ll p) {
    ll ans = 0;
    for (ll x: v) {
        if (x < p) {
            ans += p - x;
            continue;
        }
        ans += min(x % p, p - x % p);
    }
    return ans;
}
vector<ll> factors (ll n) {
    vector<ll> f;
    ll cur = n;
    for (ll i = 2; i <= sqrt(n); i++)  {
        if (cur % i == 0) {
            while (cur % i == 0) {
                cur /= i;
            }
            f.push_back(i);
        }
    }
    if (cur != 1) {
        f.push_back(cur);
    }
    return f;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<ll> v(N);
    for (ll i = 0; i < N; i++) {
        cin >> v[i];
    }
    ll ans = cost(v, 2);
    int t = 10;
    set<ll> considered;
    srand (time(NULL));
    random_shuffle(v.begin(), v.end());
    while (t--) {
        ll x = rand() % N;
        for (ll i = - 3; i <= 3; i++) {
            ll val = v[x] + i;
            if (considered.count(val)) continue;
            considered.insert(val);
            if (val >= 2) {
                for (ll f: factors(val)) {
                    ans = min(ans, cost(v, f));
                }
            }
        }
    }
    cout << ans;
}
