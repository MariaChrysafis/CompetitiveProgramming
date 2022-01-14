#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

struct segmentTree {
    vector<ll> vec;
    vector<ll> addLater;

    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const ll INF = 1e18;

    void upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            vec[dum] += val;
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r, ll val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return min(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};

vector<ll> generate_alternating_sums (vector<ll> v) {
    int n = v.size();
    vector<ll> alternating_sums(n + 1);
    alternating_sums[0] = 0;
    for (int i = 0; i < n; i++) {
        alternating_sums[i + 1] = v[i] - alternating_sums[i];
    }
    return alternating_sums;
}

bool valid (vector<ll> v) {
    vector<ll> v1 = generate_alternating_sums(v);
    for (int i: v1) {
        if (i < 0) {
            return false;
        }
    }
    return (v1.back() == 0);
}

void solve () {
    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    if (valid(v)) {
        cout << "YES\n";
        return;
    }
    vector<ll> alternating_sums_orig = generate_alternating_sums(v);
    segmentTree st[2];
    st[0].resz(n + 1), st[1].resz(n + 1);
    for (int i = 0; i < alternating_sums_orig.size(); i++) {
        st[i % 2].upd(i, i, alternating_sums_orig[i]);
        st[!(i % 2)].upd(i, i, 1e17);
    }
    for (int i = 0; i < n - 1; i++) {
        swap(v[i], v[i + 1]);
        int dif = v[i] - v[i + 1];
        st[i % 2].upd(i + 2, n, -2 * dif);
        st[(i + 1) % 2].upd(i + 2, n, 2 * dif);
        st[(i + 1) % 2].upd(i + 1, i + 1, dif);
        if (st[n % 2].get(n, n) == 0 && st[0].get(0, n) >= 0 && st[1].get(0, n) >= 0) {
            cout << "YES\n";
            return;
        }
        st[i % 2].upd(i + 2, n, 2 * dif);
        st[(i + 1) % 2].upd(i + 2, n, -2 * dif);
        st[(i + 1) % 2].upd(i + 1, i + 1, -dif);
        swap(v[i], v[i + 1]);
    }
    cout << "NO\n";
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
