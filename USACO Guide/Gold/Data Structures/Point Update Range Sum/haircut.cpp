#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <set>

#define ll long long
using namespace std;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return a + b;
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return query(dum, tl, mid, l, r) + query(dum + 1, mid + 1, tr, l, r);
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] += y;
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

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    segmentTree st;
    st.resz(n + 5);
    map<int,long long> add;
    for (int j = 0; j < n; j++) {
        add[v[j]] += st.query(v[j] + 1, n + 1);
        st.update(v[j], 1);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cout << ans << "\n";
        ans += add[i];
    }
}
