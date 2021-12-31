#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

const int MAX = 20;

set<ll> untaken;
map<ll,ll> val;

ll find_index (ll i) {
    auto it = untaken.lower_bound(i);
    if (it == untaken.end()) {
        it = untaken.begin();
    }
    ll x = *it;
    untaken.erase(x);
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 1; i <= (1 << MAX); i++) {
        untaken.insert(i);
    }
    ll Q;
    cin >> Q;
    while (Q--) {
        ll ti, xi;
        cin >> ti >> xi;
        ll orig = xi;
        xi = (xi - 1) % (1 << MAX) + 1;
        if (ti == 1) {
            val[find_index(xi)] = orig;
        } else {
            if (val[xi] == 0) {
                cout << -1 << '\n';
                continue;
            }
            cout << val[xi] << '\n';
        }
    }
}
