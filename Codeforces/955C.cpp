#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
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
vector<int> mobius = {1, 1, -1, -1, 0, -1, 1, -1, 0, 0, 1, -1, 0, -1, 1, 1, 0, -1, 0, -1, 0, 1, 1, -1, 0, 0, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, -1, 1, 1, 0, -1, -1, -1, 0, 0, 1, -1, 0, 0, 0, 1, 0, -1, 0, 1, 0, 1, 1, -1, 0};
ll eval (ll L) {
    if (L == 0) return 0;
    ll ans = 0;
    vector<int> rt(60);
    for (int i = 1; i < 60; i++) {
        rt[i] = nthRoot(L, i);
    }
    for (int i = 59; i >= 2; i--) {
        for (int j = i; j < 60; j += i) {
            ans += rt[j] * mobius[j/i];
        }
    }
    return ans - 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;
    while (Q--) {
        ll L, R;
        cin >> L >> R;
        cout << eval(R) - eval(L - 1) << '\n';
    }
}
