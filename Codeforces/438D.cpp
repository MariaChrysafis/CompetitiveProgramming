#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
struct Node {
    ll myMax;
    ll mySum;
};
struct segmentTree {
    vector<Node> val;

    Node ID = {0, 0};

    Node op(Node a, Node b) {
        return {max(a.myMax, b.myMax), a.mySum + b.mySum};
    }

    Node query(int dum, int tl, int tr, int& l, int& r) {
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

    Node query(int l, int r) {
        return query(1, 0, (int)val.size()/2 - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) val.size()/2 + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), {y, y});
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

    void update_mod (int dum, int tl, int tr, int l, int r, int MOD) {
        if (tr < l || tl > r || val[dum].myMax < MOD) {
            return;
        }
        if (tl >= l && tr <= r) {
            if (tl == tr) {
                val[dum].myMax %= MOD;
                val[dum].mySum %= MOD;
                return;
            }
        }
        ll mid = (tl + tr) >> 1;
        update_mod(2 * dum, tl, mid, l, r, MOD);
        update_mod(2 * dum + 1, mid + 1, tr, l, r, MOD);
        val[dum].myMax = max(val[2 * dum + 1].myMax, val[2 * dum].myMax);
        val[dum].mySum = val[2 * dum + 1].mySum + val[2 * dum].mySum;
    }

    void update_mod (int l, int r, int MOD) {
        update_mod(1, 0, (int)val.size()/2 - 1, l, r, MOD);
    }

    void resz(int n) {
        int sz = ceil(log2(n));
        val.assign((1 << sz) * 2, ID);
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    int N, Q;
    cin >> N >> Q;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        st.update(i, x);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << st.query(l, r).mySum << '\n';
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            st.update_mod(l, r, x);
        } else {
            int k, x;
            cin >> k >> x;
            k--;
            st.update(k, x);
        }
    }
}
