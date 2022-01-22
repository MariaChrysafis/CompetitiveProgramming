#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

void solve () {
    ll l, r, k;
    cin >> l >> r >> k;
    if (l == r && l != 1) {
        cout << "YES\n";
        return;
    }
    int odd = (r - l + 1)/2 + (l % 2 == 1 && r % 2 == 1);
    if (odd <= k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
