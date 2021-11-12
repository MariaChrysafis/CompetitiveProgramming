#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;

void solve() {
    vector<ll> v(3);
    for (int i = 0; i < 3; i++) {
        cin >> v[i];
    }
    cout << min((9ll * (ll)INT_MAX + v[0] + v[2] - 2 * v[1]) % 3, 1ll) << '\n';
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
