#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

struct segmentTree {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;
    vector<bool> marked;

    void push (int v) {
        if(marked[v]) {
            //cout << v << endl;
            marked[v] = false;
            marked[2 * v + 1] = marked[2 * v] = true;
            addLater[2 * v + 1] = addLater[2 * v] = addLater[v];
            addLater[v] = 0;
        }
    }

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] = val;
            marked[dum] = true;
            return;
        }
        push(dum);
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int)v.size() - 1, l, r, val);
    }

    ll get (int dum, int tl, int tr, ll x) {
        if(tl == tr && tl == x) {
            return addLater[dum];
        }
        push(dum);
        int tm = (tl + tr)/2;
        if(x <= tm) {
            return get(dum * 2, tl, tm, x);
        } else {
            return get(dum * 2 + 1, tm + 1, tr, x);
        }
    }

    ll get(int x) {
        return get(1, 0, v.size() - 1, x);
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
        marked.resize(vec.size());
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
            int x;
            cin >> x;
            cout << st.get(x) << '\n';
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
