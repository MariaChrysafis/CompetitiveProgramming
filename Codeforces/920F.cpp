#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

const int MAX = 1e6 + 1;

vector<int> divi;

struct Node {
    ll mySum = 0;
    int myMax = 0;
};

Node merge (Node a, Node b) {
    return {a.mySum + b.mySum, max(a.myMax, b.myMax)};
}

Node merge (Node a, Node b, Node c) {
    return {a.mySum + b.mySum + c.mySum, max(a.myMax, max(b.myMax, c.myMax))};
}
struct segmentTree {
    int sz;
    vector<Node> val;

    Node ID;

    ll find_sum (int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            return val[dum].mySum;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return find_sum(dum, tl, mid, l, r) + find_sum(dum + 1, mid + 1, tr, l, r);
    }

    Node rec (int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return merge(rec(dum, tl, mid, l, r), rec(dum + 1, mid + 1, tr, l, r));
    }

    ll find_sum (int l, int r) {
        return find_sum(1, 0, (int) sz - 1, l, r);
    }

    Node rec (int l, int r) {
        return rec(1, 0, (int) sz - 1, l, r);
    }

    void pnt_update(int x, int y) {
        int cur = (int) sz + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = merge(rec(curX, x - 1), rec(x + 1, curY), {y, y});
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

    bool rng_update (int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r || val[dum].myMax <= 2) {
            return false;
        }
        if (tl == tr) {
            val[dum] = {divi[val[dum].myMax], divi[val[dum].myMax]};
            return true;
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        bool b1 = rng_update(dum, tl, mid, l, r);
        bool b2 = rng_update(dum + 1, mid + 1, tr, l, r);
        if (b1 || b2) {
            val[dum / 2] = merge(val[dum], val[dum + 1]);
        }
        return (b1 || b2);
    }

    void rng_update (int l, int r) {
        rng_update(1, 0, sz - 1, l, r);
    }

    void resz(int n) {
        sz = (1 << (int) ceil(log2(n)));
        val.resize(sz * 2);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    divi.assign(MAX, 0);
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            divi[j]++;
        }
    }
    segmentTree st;
    int N, Q;
    cin >> N >> Q;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        st.pnt_update(i, x);
    }
    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            st.rng_update(l, r) ;
        } else {
            cout << st.find_sum(l, r) << '\n';
        }
    }
}
