#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
struct segmentTree {
    vector<ll> vec; // add later
    vector<ll> addLater; //multiply later
    vector<pair<int,int>> rng;

    void push(int v) {
        addLater[2 * v + 1] *= addLater[v];
        vec[2 * v + 1] *= addLater[v];
        addLater[2 * v] *= addLater[v];
        vec[2 * v] *= addLater[v];
        addLater[2 * v] %= MOD, vec[2 * v] %= MOD, addLater[2 * v + 1] %= MOD, vec[2 * v + 1] %= MOD;
        addLater[v] = 1;
    }

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] *= val, addLater[dum] %= MOD;
            vec[dum] *= val, vec[dum] %= MOD;
            return vec[dum];
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = (vec[2 * dum] + vec[2 * dum + 1]) % MOD);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return (get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r)) % MOD;
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void build(int dum, int l, int r) {
        vec[dum] = (r - l + 1);
        rng[dum] = {l, r};
        if(l == r) {
            return;
        }
        int m = (l + r)/2;
        build(2 * dum, l, m);
        build(2 * dum + 1, l, m);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
        rng.resize(addLater.size());
        for(int i = 0; i < addLater.size(); i++) {
            addLater[i] = 1;
        }
        build(1, 0, (int)vec.size()/2 - 1);
    }

};

void solve() {
    segmentTree st;
    int n, q;
    cin >> n >> q;
    st.resz(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            ll x, y, v;
            cin >> x >> y >> v;
            st.upd(x, y - 1, v);
        } else {
            int x, y;
            cin >> x >> y;
            cout << st.get(x, y - 1) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
