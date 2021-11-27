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
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,pair<int,int>>> v(m);
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> v[i].second.first >> v[i].second.second >> v[i].first;
        v[i].second.first--, v[i].second.second--;
       ans = ans | v[i].first;
    }
    cout << (ans * binPow(2, n - 1)) % MOD << '\n';

}

int main()  {
        int t;
        cin >> t;
        while (t--) {
            solve();
        }
}
