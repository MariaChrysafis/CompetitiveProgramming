#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
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
        y >>= 1;
    }
    return ans;
}
void solve() {
    string s;
    cin >> s;
    ll l = 0;
    ll r = 0;
    ll len = 0;
    int cnt = 0;
    for (int i = 0; i < s.length()/2; i++) {
        l += (binPow(10, len) * (s[i] - 'a')) % MOD;
        r = ((10 * r) % MOD + (s[s.length() - i -1 ] - 'a')) % MOD;
        l %= MOD, r %= MOD;
        len++;
        if (l == r) {
            cnt += 2;
            l = r = len = 0;
        } else if (s.length() % 2 == 0 && i == s.length()/2 - 1) {
            cnt++;
        }
    }
    if (s.length() % 2 == 1) {
        cnt++;
    }
    cout << cnt << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
