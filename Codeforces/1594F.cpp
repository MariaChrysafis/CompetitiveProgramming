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

#define ll long long
using namespace std;

ll ceil (ll n, ll k) {
    return (n + k - 1)/k;
}

bool solve (ll s, ll n, ll k) {
    if (k == s) {
        return true;
    }
    if (k > s ) {
        return false;
    }
    if (s < n) {
        return false;
    }
    if (s == n) {
        return true;
    }
    return (n/k * k + n > s);
}

int32_t main() {
    srand (time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll s, n, k;
        cin >> s >> n >> k;
        bool b = solve(s, n, k);
        if (b) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

}
