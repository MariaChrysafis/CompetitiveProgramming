#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;

typedef int64_t ll;

void solve () {
    int N;
    cin >> N;
    ll myMin = 1e10;
    ll myMax = 0;
    set<pair<ll,ll>> s;
    map<ll,ll> costL, costR;
    map<pair<ll,ll>,ll> cost;
    for (int i = 0; i < N; i++) {
        ll l, r, c;
        cin >> l >> r >> c;
        myMin = min(myMin, l);
        myMax = max(myMax, r);
        if (costL[l]) costL[l] = min(costL[l], c);
        else costL[l] = c;
        if (costR[r]) costR[r] = min(costR[r], c);
        else costR[r] = c;
        if (cost[{l, r}]) cost[{l, r}] = min(cost[{l, r}], c);
        else cost[{l, r}] = c;
        if (cost[{myMin, myMax}]) {
            cout << min(cost[{myMin, myMax}], costL[myMin] + costR[myMax]) << '\n';
        } else {
            cout << costL[myMin] + costR[myMax] << '\n';
        }
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
