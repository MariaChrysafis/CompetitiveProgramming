#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
const int MAX = 71;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
    int n;
    cin >> n;
    vector<int> oc;
    oc.assign(MAX, 0);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (auto& p: primes) {
            while (a[i] % (p * p) == 0) {
                a[i] /= p * p;
            }
        }
        oc[a[i]]++;
    }
    ll prev[(1 << primes.size())], cur[(1 << primes.size())];
    for (int j = 0; j < (1 << primes.size()); j++) {
        prev[j] = cur[j] = 0;
    }
    prev[0] = 1;
    for (int i = 1; i < MAX; i++) {
        int mask = 0;
        for (int j = 0; j < primes.size(); j++) {
            if (i % primes[j] == 0) {
                mask += (1 << j);
            }
        }
        for (int j = 0; j < (1 << primes.size()); j++) {
            cur[j] = mult(prev[j], binPow(2, max(oc[i] - 1, 0)));
            if (oc[i]) {
                cur[j] += mult(prev[mask ^ j], binPow(2, oc[i] - 1));
            }
            cur[j] %= MOD;
        }
        for (int j = 0; j < (1 << primes.size()); j++) {
            prev[j] = cur[j];
            cur[j] = 0;
        }
    }
    cout << prev[0] - 1;
}
