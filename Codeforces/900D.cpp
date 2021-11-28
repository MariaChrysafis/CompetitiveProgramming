#include <iostream>
#include <cmath>
#include <cassert>
#include <set>
#define ll long long
using namespace std;
ll mobius(ll x) {
    for (ll i = 2; i <= sqrt(x); i++) {
        if (x % (i * i) == 0) {
            return 0;
        }
    }
    ll last = x;
    ll cntr = 0;
    for (int i = 2; i <= sqrt(last); i++) {
        if (x % i == 0) {
            cntr++;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x != 1) {
        cntr++;
    }
    if (cntr % 2 == 0) {
        return 1;
    } else {
        return -1;
    }
}
set<ll> factors (ll x) {
    set<ll> s;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            s.insert(i);
            s.insert(x/i);
        }
    }
    return s;
}
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll x, y;
    cin >> x >> y;
    if (y % x != 0) {
        cout << 0;
        return 0;
    }
    y /= x;
    x = 1;
    ll ans = 0;
    for (int i: factors(y)) {
        ans += binPow(2, i - 1) * mobius(y/i);
        ans += MOD;
        ans %= MOD;
    }
    cout << ans;
}
