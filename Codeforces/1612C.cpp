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
ll emotes (ll rows, ll k) {
    //we do row rows
    if (rows <= k) {
        return rows * (rows + 1)/2;
    }
    rows -= k;
    return k * (k + 1)/2 + (2 * k - 1 - rows) * rows/2;
}
void solve() {
    ll k, x;
    cin >> k >> x;
    ll l = 0;
    ll r = 2 * k - 1;
    while (l != r) {
        ll m = (l + r)/2;
        if (emotes(m, k) >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
