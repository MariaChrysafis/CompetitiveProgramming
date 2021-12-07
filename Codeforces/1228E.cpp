#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
using namespace std;
ll combo[251][251];
const ll MOD = 1e9 + 7;
ll binPow (ll x, ll y) {
    x %= MOD;
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
void fill_combo() {
    for (int i = 0; i < 251; i++) {
        for (int j = 0; j < 251; j++) {
            if (i == j || j == 0) {
                combo[i][j] = 1;
            } else if (i < j) {
                combo[i][j] = 0;
            } else {
                combo[i][j] = combo[i - 1][j] + combo[i - 1][j - 1];
                combo[i][j] %= MOD;
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fill_combo();
    ll n, k;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ll res = mult(binPow(k, n - i) - binPow(k - 1, n - i) + MOD, binPow(k - 1, i));
        res = binPow(res, n);
        if (i % 2 == 0) {
            res *= combo[n][i], res %= MOD;
        } else {
            res = MOD - res; res *= combo[n][i], res %= MOD;
        }
        //res *= combo[n][i] * pow(-1, i % 2);
        res %= MOD;
        ans += res;
        ans %= MOD;
    }
    cout << ans;
}
