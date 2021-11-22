#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#define ll __uint128_t
using namespace std;
ll powr (ll x) {
    if (x == 0) return 1;
    return powr(x - 1) * 2;
}
ll log (ll x) {
    for (int i = 60; i >= 0; i--) {
        if (powr(i) <= x) {
            return i;
        }
    }
    assert(false);
}
ll find_oc_odd (ll x, ll y) {
    //find the number of occurences of y if we do things 1...x
    if (y > x) {
        return 0;
    }
    ll l = 1;
    ll r = x;
    while (l < r) {
        ll m = (l + r + 1)/2;
        ll base = log(m);
        ll ans = powr(base) * y;
        ans += m - powr(base);
        if (ans <= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}
ll find_oc_even (ll x, ll y) {
    if (y > x) {
        return 0;
    }
    ll l = 1;
    ll r = x;
    while (l < r) {
        ll m = (l + r + 1)/2;
        ll base = log(m + 1) - 1;
        ll ans = powr(base) * y + m - powr(base + 1) + 1;
        if (ans <= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}
ll binSearchOdd (ll x, ll k) {
    ll l = 1;
    ll r = x;
    while (l < r) {
        ll m = (l + r + 1)/2;
        if (find_oc_odd(x, 2 * m - 1) < k) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return 2 * r - 1;
}

ll binSearchEven (ll x, ll k) {
    ll l = 0;
    ll r = x;
    while (l < r) {
        ll m = (l + r + 1)/2;
        if (find_oc_even(x, 2 * m) < k) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return 2ll * l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long x1, k1;
    cin >> x1 >> k1;
    ll x, k;
    x = x1, k = k1;
    long long ans = max(binSearchOdd(x, k), binSearchEven(x, k));
    cout << ans;
}
