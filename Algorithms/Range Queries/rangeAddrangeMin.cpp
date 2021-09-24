#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

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

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        ll left = upd(2 * dum, tl, mid, l, r, val);
        ll right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int val) {
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
        /*
        for (int i: st.addLater) {
            cout << i << " ";
        }
        cout << '\n';
         */
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
