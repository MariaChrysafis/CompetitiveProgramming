#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
class segmentTree {
    vector<ll> vec;
    vector<ll> addLater;

public:
    segmentTree(ll n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

public:
    void push(ll v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const ll INF = LLONG_MAX;

    void upd(ll dum, ll tl, ll tr, ll l, ll r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            vec[dum] += val;
            return;
        }
        push(dum);
        ll mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(ll l, ll r, ll val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(ll dum, ll tl, ll tr, ll &l, ll &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        ll tm = (tl + tr) >> 1;
        return min(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(ll l, ll r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

};
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> p(n);
    vector<ll> cost(n);
    segmentTree st(n + 2); //st[i] -> the minimum cost if it's 0...i|i+1...N
    vector<ll> ip(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        ip[p[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    ll pref = cost[0];
    for (int i = 1; i <= n; i++) {
        st.upd(i, i, pref);
        if (i != n) {
            pref += cost[i];
        }
    }
    ll ans = min(cost[0], cost[n - 1]);
    for (int i = 0; i < n; i++) {
        ans = min(ans, st.get(1, n - 1));
        st.upd(0, ip[i], cost[ip[i]]);
        st.upd(ip[i] + 1, n, -cost[ip[i]]);
    }
    ans = min(ans, st.get(1, n - 1));
    cout << ans;
}
