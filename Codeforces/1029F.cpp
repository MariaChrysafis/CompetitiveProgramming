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

set<pair<ll, ll>> generate(ll area) {
    set<pair<ll, ll>> vec;
    for (ll i = 1; i <= 16000000ll; i++) {
        if (area % i == 0) {
            vec.insert({i, area / i});
            vec.insert({area/i, i});
        }
    }
    return vec;
}

ll solve(ll a, ll b) {
    set<pair<ll, ll>> ab = generate(a + b);
    set<pair<ll, ll>> va = generate(a);
    ll myMin = LLONG_MAX;
    for (auto &p: ab) {
        auto it = va.upper_bound({p.first, -1});
        if (it == va.begin()) continue;
        it--;
        pair<ll, ll> q = *it;
        if (q.first <= p.first && q.second <= p.second) {
            myMin = min(myMin, p.first + p.second);
        }
    }
    return myMin;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll a, b;
    cin >> a >> b;
    cout << 2 * min(solve(a, b), solve(b, a));
}
