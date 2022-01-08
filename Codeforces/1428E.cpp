#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

pair<ll,ll> types (ll x, ll i) {
    //split x into i pieces
    if (x % i == 0) {
        return {i, 0};
    }
    int b = x - i * (ll)(x/i);
    int a = i - b;
    return {a, b};
}

ll partition_cost (ll x, ll i) {
    //cost if we partition x into i pieces
    pair<ll, ll> p = types(x, i);
    ll t1 = (ll)(x/i);
    return t1 * t1 * p.first + (t1 + 1) * (t1 + 1) * p.second;
}

struct Type {
    ll cur;
    ll splits;
    ll nxt_gain;
    ll ind;
    bool operator < (const Type& type) const {
        if (type.nxt_gain != nxt_gain) return (type.nxt_gain < nxt_gain);
        return (type.ind < ind);
    }
    void print () {
        cout << cur << " " << ind << " " << splits << " " << nxt_gain << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vector<ll> a(N);
    set<Type> s;
    ll cost = 0;
    //cout << partition_cost(5, 4) << " " << partition_cost(5, 5) << '\n';
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        cost += a[i] * a[i];
        //cout << partition_cost(a[i], 1ll) << " " << partition_cost(a[i], 2ll) << '\n';
        s.insert({a[i], 1, partition_cost(a[i], 1ll) - partition_cost(a[i], 2ll), i});
    }
    K -= N;
    while (K--) {
        auto it = s.begin();
        Type t = *it;
        //cout << t.cur << '\n';
        s.erase(t);
        Type nxt;
        nxt.cur = t.cur;
        nxt.ind = t.ind;
        nxt.splits = ++t.splits;
        nxt.nxt_gain = partition_cost(a[nxt.ind], nxt.splits) - partition_cost(a[nxt.ind], nxt.splits + 1);
        cost -= t.nxt_gain;
        s.insert(nxt);
        //cout << cost << '\n';
    }
    cout << cost;
}
