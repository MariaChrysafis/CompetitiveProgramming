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
    int l;
    int r;
    int val;
    bool mn;
};

Node INF = {-1, -1, -1, false};

Node merge (Node left, Node right) {
    if (left.l == -1) {
        return right;
    } else if (right.l == -1) {
        return left;
    }
    return (Node){left.l + right.l * left.mn, right.r + left.r * right.mn, max(left.r + right.l, max(left.val, right.val)), (left.mn && right.mn)};
}

struct SegmentTree {
    vector<Node> vec;
    vector<int> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] == -1) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = {setLater[v] * (tr - tm),setLater[v] * (tr - tm),setLater[v] * (tr - tm),(bool)setLater[v]};
        setLater[2 * v] = setLater[v];
        vec[2 * v] = {setLater[v] * (tm - tl + 1),setLater[v] * (tm - tl + 1),setLater[v] * (tm - tl + 1),(bool)setLater[v]};
        setLater[v] = -1;
    }

    void upd(int dum, int tl, int tr, int l, int r, bool val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            vec[dum] = {val * (tr - tl + 1),val * (tr - tl + 1),val * (tr - tl + 1), val};
            return;
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = merge(vec[2 * dum],vec[2 * dum + 1]);
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
        return merge(get(dum * 2, tl, tm, l, r),get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, {1,1,1,1});
        setLater.assign(sz * 2, -1);
    }

    void seat (int dum, int tl, int tr, int x) {
        push(dum, tl, tr);
        if (x == tr - tl + 1) {
            upd(tl, tr, 0);
            return;
        }
        if (vec[2 * dum].val >= x) {
            seat (2 * dum, tl, (tl + tr)/2, x);
        } else if (vec[2 * dum].r + vec[2 * dum + 1].l >= x) {
            upd((tl + tr)/2 - vec[2 * dum].r + 1, (tl + tr)/2 - vec[2 * dum].r + x, 0);
        } else if (vec[2 * dum + 1].val >= x) {
            seat(2 * dum + 1, (tl + tr)/2 + 1, tr, x);
        }
    }
    void seat (int x) {
        seat(1, 0, (int)vec.size()/2 - 1, x);
    }
};

int main() {
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, D;
    cin >> N >> D;
    SegmentTree st;
    st.resz(N);
    st.upd(0, N - 1, 1);
    int cntr = 0;
    while (D--) {
        char c; cin >> c;
        if (c == 'A') {
            int x;
            cin >> x;
            if (st.get(0, N - 1).val < x) {
                cntr++;
                continue;
            }
            st.seat(x);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            st.upd(l, r, 1);
        }
    }
    cout << cntr;
}
