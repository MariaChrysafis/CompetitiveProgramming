#include <iostream>
#include <cmath>
#include <cassert>
#define ll long long
using namespace std;
int mobius(int x) {
    for (int i = 2; i <= x; i++) {
        if (x % (i * i) == 0) {
            return 0;
        }
    }
    int last = x;
    int cntr = 0;
    for (int i = 2; i <= last; i++) {
        if (x % i == 0) {
            cntr++;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (cntr % 2 == 0) {
        return 1;
    } else {
        return -1;
    }
}
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
        }
        res *= res;
        y /= 2;
    }
    return ans;
}
ll nthRoot (long double x, long double y) {
    if (y == 1) return x;
    if (y == 2) return floor(sqrt(x));
    if (y == 3) return floor(cbrt(x));
    double ans = pow(x, 1.0/y);
    ll res = floor(ans);
    while (binPow(res, y) > x) {
        res--;
    }
    assert (binPow(res, y) <= x);
    return res;
}
int m[61];
void solver (ll x) {
    //how many things from 1...x have a range gcd exactly equal to x
    ll f[61]; //f[i] -> how many things from 1...x have a range gcd which is some multiple of i
    f[0] = 1;
    for (int i = 1; i < 61; i++) {
        f[i] = nthRoot(x, i);
    }
    ll g[61];
    for (int i = 60; i >= 1; i--) {
        g[i] = 0;
        for (int j = i; j <= 60; j += i) {
            g[i] += f[j] * m[j/i];
        }
    }
    cout << g[1] + 1 << '\n';
}
int main() {
    for (int i = 0; i < 61; i++) {
        m[i] = mobius(i);
    }
    int first = 0;
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        ll x;
        cin >> x;
        solver(x);
    }
}
