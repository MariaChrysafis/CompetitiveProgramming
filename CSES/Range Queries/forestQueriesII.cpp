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
 
template<class T>
class SegmentTree1D {
public:
    vector<T> val;
    SegmentTree1D (int N) {
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
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
 
template<class T>
class SegmentTree2D {
public:
    SegmentTree2D (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, SegmentTree1D<T>(N));
    }
 
    void update (int x, int y, T z) {
        x += N - 1;
        val[x].update(y, z);
        T new_z = z;
        while (x != 0) {
            x = (x - 1)/2;
            new_z = (merge(val[2 * x + 1].val[y + N - 1], val[2 * x + 2].val[y + N - 1]));
            val[x].update(y, new_z);
        }
    }
 
    T query (int ind, const int lx, const int rx, const int ly, const int ry, int tl, int tr) {
        if (tl >= lx && tr <= rx) {
            return val[ind].query(ly, ry);
        }
        if (tr < lx || tl > rx) {
            return ID;
        }
        return merge(query(2 * ind + 1, lx, rx, ly, ry, tl, (tl + tr) / 2), query(2 * ind + 2, lx, rx, ly, ry, (tl + tr) / 2 + 1, tr));
    }
 
    T query (int lx, int rx, int ly, int ry) {
        return query(0, lx, rx, ly, ry, 0, N - 1);
    }
private:
    vector<SegmentTree1D<T>> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    SegmentTree2D<int64_t> st(N);
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (int j = 0; j < N; j++) {
            if (s[j] == '*') {
                st.update(i, j, 1);
            } else {
                st.update(i, j, 0);
            }
        }
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y; x--, y--;
            if (st.query(x, x, y, y) == 1) {
                st.update(x, y, 0);
            } else {
                st.update(x, y, 1);
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            cout << st.query(x1, x2, y1, y2) << '\n';
        }
    }
}
