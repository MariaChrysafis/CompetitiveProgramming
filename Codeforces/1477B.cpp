#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#define ll long long
using namespace std;
struct segmentTree {
    vector<ll> vec;
    vector<ll> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] == -1) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = setLater[v] * (tr - tm);
        setLater[2 * v] = setLater[v];
        vec[2 * v] = setLater[v] * (tm - tl + 1);
        setLater[v] = -1;
    }

    const ll INF = 0;

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            return (vec[dum] = val * (tr - tl + 1));
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
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
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, -1);
    }

};
bool solve() {
    int n, q;
    cin >> n >> q;
    string s, f; //start and final
    cin >> s >> f; //start and final
    vector<pair<int,int>> vec;
    segmentTree st;
    st.resz(f.size());
    for (int i = 0; i < f.size(); i++) {
        st.upd(i, i, f[i] - '0');
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vec.emplace_back(l, r);
    }
    reverse(vec.begin(), vec.end());
    for (auto& p: vec) {
        int ones = st.get(p.first, p.second);
        int zeroes = p.second - p.first + 1 - ones;
        if (ones == zeroes) {
            return false;
        }
        if (ones > zeroes) {
            st.upd(p.first, p.second, 1);
        } else {
            st.upd(p.first, p.second, 0);
        }
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] - '0' != st.get(i, i)) {
            return false;
        }
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
}
