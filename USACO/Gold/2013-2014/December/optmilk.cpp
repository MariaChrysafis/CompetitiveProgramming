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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
const int MOD = 1e9;

class Node {
public:
    int64_t arr[2][2];
};

template<class T>
class SegmentTree {
public:
    vector<T> val;
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    T ID = {0, 0, 0, 0};
    T merge (T x, T y) {
        Node ans;
        for (int a = 0; a <= 1; a++) {
            for (int b = 0; b <= 1; b++) {
                ans.arr[a][b] = max(max(x.arr[a][1] + y.arr[0][b], x.arr[a][0] + y.arr[1][b]), x.arr[a][0] + y.arr[0][b]);
            }
        }
        return ans;
    }
    int N;
};

Node get_node (int64_t x) {
    Node ans;
    ans.arr[0][0] = 0;
    ans.arr[1][0] = ans.arr[0][1] = -INT_MAX;
    ans.arr[1][1] = x;
    return ans;
}

int64_t get_max (Node myNode) {
    int64_t myMax = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            myMax = max(myMax, myNode.arr[i][j]);
        }
    }
    return myMax;
}


int main() {
    freopen("optmilk.in", "r", stdin);
    freopen("optmilk.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, D;
    cin >> N >> D;
    SegmentTree<Node> st(N);
    for (int i = 0; i < N; i++) {
        int64_t x; cin >> x;
        st.update(i, get_node(x));
    }
    int64_t ans = 0;
    while (D--) {
        int64_t i, m;
        cin >> i >> m;
        st.update(i - 1, get_node(m));
        ans += get_max(st.query(0, N - 1));
    }
    cout << ans;
}
