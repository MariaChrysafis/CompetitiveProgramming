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
ll gcd (ll a, ll b) {
    if (min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve() {
    ll n, m;
    cin >> n >> m;
    ll c[n];
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> adj_r(n); //what's adjacent to some rightmost thing (rightmost -> leftmost)
    map<vector<int>, vector<int>> myMap;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj_r[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        sort(adj_r[i].begin(), adj_r[i].end());
        myMap[adj_r[i]].push_back(i);
    }
    for (auto& p: myMap) {
        ll sum = 0;
        for (int i: p.second) {
            sum += c[i];
        }
        for (int i: p.second) {
            c[i] = sum;
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (!adj_r[i].empty()) {
            ans = gcd(ans, c[i]);
        }
    }
    cout << ans << '\n';
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
