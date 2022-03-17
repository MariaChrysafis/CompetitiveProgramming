#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>

using namespace std;
const int MOD = 1e9;

class Node {
public:
    int64_t tot;
    int64_t mn;
};


Node merge (Node left, Node right) {
    return {left.tot + right.tot, min(left.mn, right.mn)};
}

struct segmentTree {
    vector<Node> vec;
    vector<int64_t> addLater;

    void push(int v, int l, int r) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1].mn += addLater[v];
        vec[2 * v + 1].tot += addLater[v] * (r - ((l + r)/2 + 1) + 1);
        addLater[2 * v] += addLater[v];
        vec[2 * v].mn += addLater[v];
        vec[2 * v].tot += addLater[v] * ((l + r)/2 - l + 1);
        addLater[v] = 0;
    }

    const Node INF = {0, LLONG_MAX};

    void upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            vec[dum].mn += val;
            vec[dum].tot += (tr - tl + 1) * val;
            return;
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    Node get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return merge(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, D;
    cin >> N >> D;
    segmentTree st;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        st.upd(i, i, x);
        //cout << st.get(i, i).tot << '\n';
    }
    while (D--) {
        char c; cin >> c;
        if (c == 'M') {
            int l, r; cin >> l >> r; l--, r--;
            cout << st.get(l, r).mn << '\n';
        } else if (c == 'P') {
            int l, r, v; cin >> l >> r >> v; l--, r--;
            st.upd(l, r, v);
        } else if (c == 'S') {
            int l, r; cin >> l >> r; l--, r--;
            cout << st.get(l, r).tot << '\n';
        }
    }
}
