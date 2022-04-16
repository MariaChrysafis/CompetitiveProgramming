#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <set>
using namespace std;
template <typename T>
class SegmentTree {
public:
    SegmentTree (int n) {
        val.assign((1 << ((int)ceil(log2(n)) + 1)), 0);
    }
    vector<T> val;
    T id = 0;
    void update (int x, T y) {
        x += (int)val.size()/2 - 1;
        val[x] += y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }
    T query (int dum, int tl, int tr, int l, int r) {
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        if (r < tl || l > tr) {
            return id;
        }
        return merge(query(2 * dum + 1, tl, (tl + tr)/2, l, r), query(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r));
    }
    T query (int l, int r) {
        return query(0, 0, (int)val.size()/2 - 1, l, r);
    }
    T merge (T x, T y) {
        return x + y;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    SegmentTree<int64_t> st(N);
    for (int i = 0; i < N; i++) {
        int64_t x; cin >> x;
        st.update(i, x);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r; cin >> l >> r;
            cout << st.query(l, r - 1) << '\n';
        } else {
            int p, x; cin >> p >> x;
            st.update(p, x);
        }
    }
}
