#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 2e15;

    ll op(ll a, ll b) {
        return min(a,b);
    }

    ll query(ll dum, ll tl, ll tr, ll& l, ll& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(ll l, ll r) {
        return query(1, 0, (ll)v.size() - 1, l, r);
    }

    void update(ll x, ll y) {
        ll cur = (ll) v.size() + x;
        ll curX = x;
        ll curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(ll n) {
        v.resize((1 << (ll) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
void solve () {
    ll n, s;
    cin >> n >> s;
    vector<ll> v(n);
    for (ll i = 0; i < v.size(); i++) {
        cin >> v[i];
    }
    vector<pair<ll,ll>> vec;
    vector<ll> pref(n + 1);
    pref[0] = 0;
    for (ll i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + v[i - 1];
    }
    segmentTree st;
    st.resz(n + 1);
    for (ll i = 0; i <= n; i++) {
        st.update(i, pref[i]);
    }
    //cout << st.query(1, 2) << '\n';
    for (ll i = 0; i < n; i++) {
        if (v[i] + s < 0) {
            continue;
        }
        ll l = i;
        ll r = n - 1;
        while (l < r) {
            ll m = (l + r + 1)/2;
            //cout << l << " ? " << r << " ? " << m << "|" << st.query(i + 1, m + 1) << '\n';
            if (st.query(i + 1, m + 1) - pref[i] + s < 0) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        //cout << i << " " << l << " " << r << '\n';
        vec.push_back({i, l});
    }
    if (vec.empty()) {
        cout << "-1\n";
        return;
    }
    pair<ll,ll> best = {0, -1};
    for (auto& p: vec) {
        if (p.second - p.first > best.second - best.first) {
            best = p;
        }
    }
    cout << best.first + 1 << " " << best.second + 1<< '\n';
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
