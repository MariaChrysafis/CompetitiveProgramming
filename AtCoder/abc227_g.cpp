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

map<ll,ll> cnt;

bool isPrime (ll x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

const int MOD = 998244353;

set<ll> sieve (ll N) {
    vector<bool> primes(N);
    for (int i = 0; i < N; i++) {
        primes[i] = true;
    }
    primes[0] = primes[1] = false;
    for (int i = 0; i < N; i++) {
        if (primes[i]) {
            for (int j = 2 * i; j < N; j += i) {
                primes[j] = false;
            }
        }
    }
    set<ll> p;
    for (int i = 0; i < N; i++) {
        if (primes[i]) {
            p.insert(i);
        }
    }
    return p;
}

set<ll> primes;

void upd (ll K, ll inc) {
    for (ll i: primes) {
        ll powr = i;
        while (K/powr != 0) {
            cnt[i] += K/powr * inc;
            powr *= i;
        }
    }
}

const ll MAX = 1e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    primes = sieve(MAX);
    ll isPrime[K]; //isPrime[i] corresponds to N - i
    for (ll i = 0; i < K; i++) {
        isPrime[i] = N - i;
    }
    for (ll i: primes) {
        //N - K + 1
        ll st = (N - K + 1 + i - 1)/i * i;
        for (ll x = st; x <= N; x += i) {
            while (isPrime[N - x] % i == 0) {
                isPrime[N - x] /= i;
            }
        }
    }
    for (ll i = max(N - K + 1, MAX); i <= N; i++) {
        if (isPrime[N - i]) {
            primes.insert(isPrime[N - i]);
        }
    }
    primes.erase(1);
    upd(N, 1);
    upd(N - K, -1);
    upd(K, -1);
    cnt[1] = 0;
    ll ans = 1;
    for (ll p: primes) {
        //cout << p << " " << cnt[p] << '\n';
        ans *= (cnt[p] + 1);
        ans %= MOD;
    }
    cout << ans;
}
