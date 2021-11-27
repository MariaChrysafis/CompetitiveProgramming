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
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
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

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
struct Query {
    int l, r, x;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    int n, m;
    cin >> n >> m;
    st.resz(n + 2);
    vector<int> val_to_pos(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        val_to_pos[p[i]] = i;
    }
    vector<vector<pair<Query,int>>> vec(n);
    for (int i = 0; i < m; i++) {
        Query q;
        cin >> q.l >> q.r >> q.x;
        pair<Query,int> pr;
        pr.second = i;
        q.l--, q.r--, q.x--;
        pr.first = q;
        vec[p[q.x]].push_back(pr);
    }
    bool ans[m];
    for (int i = 0; i < n; i++) {
        st.update(val_to_pos[i], 1);
        for (auto &pr: vec[i]) {
            Query q = pr.first;
            if (q.x > q.r || q.x < q.l) {
                ans[pr.second] = false;
                continue;
            }
            ans[pr.second] = (st.query(q.l, q.r) != q.x - q.l + 1);
        }
    }
    for (int i = 0; i < m; i++) {
        //cout << ans[i] << '\n';
        if (ans[i]) cout << "No\n";
        else cout << "Yes\n";
    }
}
