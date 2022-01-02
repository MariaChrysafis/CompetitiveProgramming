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
const int MAX = 5e5 + 1;
vector<ll> primes;
vector<ll> reduce;
vector<int> mu;
vector<vector<int>> factors;
void sieve () {
    vector<bool> isPrime;
    isPrime.assign(MAX, true);
    reduce.assign(MAX, 0);
    for (int i = 2; i < isPrime.size(); i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            reduce[i] = i;
            for (int j = 2 * i; j < isPrime.size(); j += i) {
                isPrime[j] = false;
            }
        }
    }
    reduce[1] = 1;
    for (int i = 2; i < isPrime.size(); i++) {
        if (reduce[i]) {
            continue;
        }
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % (j * j) == 0) {
                reduce[i] = reduce[i/j];
            }
        }
        if (!reduce[i]) {
            reduce[i] = i;
        }
    }
    vector<int> lpf(MAX);
    lpf.assign(MAX, 0);
    for (int i = 2; i < MAX; i++) {
        if (!lpf[i]) {
            for (int j = i; j < MAX; j += i) {
                if (!lpf[j]) {
                    lpf[j] = i;
                }
            }
        }
    }
    mu.assign(MAX, 0);
    mu[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (lpf[i/lpf[i]] == lpf[i]) {
            mu[i] = 0;
            continue;
        }
        mu[i] = -1 * mu[i/lpf[i]];
    }
    factors.resize(MAX);
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            if (reduce[j] == j) {
                factors[j].push_back(i);
            }
        }
    }
}
set<int> indices;
vector<ll> oc(MAX);
ll ans = 0;
void upd (int ind, int val) {
    ans -= oc[ind] * (oc[ind] - 1)/2 * mu[ind];
    oc[ind] += val;
    ans += oc[ind] * (oc[ind] - 1)/2 * mu[ind];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = reduce[a[i]];
    }
    oc.assign(MAX, 0);
    while (q--) {
        int x;
        cin >> x;
        x--;
        if (indices.count(x)) {
            for (int j: factors[a[x]]) {
                upd(j, -1);
            }
            indices.erase(x);
        } else {
            for (int j: factors[a[x]]) {
                //cout << j << ' ';
                upd(j, 1);
            }
            //cout << '\n';
            indices.insert(x);
        }
        cout << ans << '\n';
    }



}
