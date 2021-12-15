#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define pb push_back
#define mp make_pair

#define ll long long
using namespace std;
bool valid (vector<ll> v1, vector<ll> v2, ll g) {
    for (ll i: v1) {
        if (i % g != 0) {
            return false;
        }
    }
    for (ll i: v2) {
        if (i % g == 0) {
            return false;
        }
    }
    return true;
}
ll gcd (ll a, ll b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> v[2];
        ll g[2];
        g[0] = g[1] = 0;
        for (ll i = 0; i < n; i++) {
            ll x; cin >> x;
            v[i % 2].push_back(x);
            g[i % 2] = gcd(g[i % 2], x);
        }
        bool marked = false;
        if (valid(v[0], v[1], g[0])) {
            cout << g[0] << '\n';
            continue;
        }
        if (valid(v[1], v[0], g[1])) {
            cout << g[1] << '\n';
            continue;
        }
        cout << 0 << '\n';
    }


}
