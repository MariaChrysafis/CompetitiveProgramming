#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

const ll MOD = 1e9 + 7;

using namespace std;

ll l = 0;
ll r = 1000;

ll x = 5;
ll n;

/*
ll n = 21;

ll query (ll c) {
    l += c, r += c;
    x += c;
    l = max(l, n * x/n);
    r = min(r, n * (x/n + 1) - 1);
    return x/n;
}
 */
ll query (ll c) {
    cout << "+ " << c << '\n';
    cout.flush();
    x += c;
    ll val;
    cin >> val;
    return val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int pref = 0;
    while (l < r) {
        //cout << l << " " << r << " " << r - l << '\n';
        //cout << l - pref << " " << r - pref << '\n';
        ll mid = n - ((l + r + 1)/2) % n;
        if (mid == n) {
            mid--;
        }
        pref += mid;
        ll val = query(mid);
        l += mid, r += mid;
        l = max(l, n * val);
        r = min(r, n * (val + 1) - 1);
    }
    cout << "! " << l;
}
