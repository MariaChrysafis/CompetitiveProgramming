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
 
class Node {
public:
    int64_t sum = 0;
    int64_t max_prefix_sum = 0;
    int tl, tr;
};
 
template<class T>
class SegmentTree {
public:
 
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
        ID.tl = -1;
    }
 
    void build (vector<int64_t>& arr, int dum, int tl, int tr) {
        if (tl == tr) {
            val[dum].sum = arr[tl];
            val[dum].max_prefix_sum = arr[tl];
            if (val[dum].max_prefix_sum < 0) {
                val[dum].max_prefix_sum = 0;
            }
            val[dum].tl = val[dum].tr = tl;
            return;
        }
        build(arr,2 * dum + 1, tl, (tl + tr)/2);
        build(arr,2 * dum + 2, (tl + tr)/2 + 1, tr);
        val[dum] = merge(val[2 * dum + 1], val[2 * dum + 2]);
    }
 
    SegmentTree (int N, vector<int64_t> arr) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
        build(arr, 0, 0, N - 1);
        ID.tl = -1;
    }
 
    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }
 
    T getter (int x, int y) {
        x += N - 1;
        T ans;
        ans.sum = y;
        ans.max_prefix_sum = max(y, 0);
        ans.tl = ans.tr = x;
        return ans;
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
    vector<T> val;
    T ID;
    T merge (T x, T y) {
        if (x.tl == -1) return y;
        if (y.tl == -1) return x;
        T ans;
        ans.sum = x.sum + y.sum;
        ans.max_prefix_sum = max(x.max_prefix_sum, x.sum + y.max_prefix_sum);
        return ans;
    }
    int N;
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, D;
    cin >> N >> D;
    vector<int64_t> arr(N);
    for (int64_t i = 0; i < N; i++) {
        cin >> arr[i];
    }
    SegmentTree<Node> st(N, arr);
    while (D--) {
        int t;
        cin >> t;
        if (t == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << st.query(a, b).max_prefix_sum << '\n';
        } else {
            int k, u;
            cin >> k >> u;
            k--;
            st.update(k, st.getter(k, u));
        }
    }
}
