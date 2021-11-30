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
