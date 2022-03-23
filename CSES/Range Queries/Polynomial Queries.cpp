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
    int64_t tl, tr;
};
 
template<class T>
class SegmentTree {
    vector<T> vec;
    vector<int64_t> addLater;
    vector<int64_t> incLater;
 
    void push(int64_t dum) {
        for (int64_t c = 1; c <= 2; c++) {
            vec[2 * dum + c].sum += incLater[dum] * (vec[2 * dum + c].tr - vec[2 * dum + c].tl + 1) * (vec[2 * dum + c].tr - vec[2 * dum + c].tl + 2) / 2;
            vec[2 * dum + c].sum += addLater[dum] * (vec[2 * dum + c].tr - vec[2 * dum + c].tl + 1);
        }
        vec[2 * dum + 2].sum += incLater[dum] * abs(vec[2 * dum + 1].tr - vec[2 * dum + 1].tl + 1) * abs(vec[2 * dum + 2].tr - vec[2 * dum + 2].tl + 1);
        for (int64_t c = 1; c <= 2; c++) {
            addLater[2 * dum + c] += addLater[dum];
            incLater[2 * dum + c] += incLater[dum];
        }
        addLater[2 * dum + 2] += abs(vec[2 * dum + 1].tr - vec[2 * dum + 1].tl + 1) * incLater[dum];
        addLater[dum] = 0;
        incLater[dum] = 0;
    }
 
    T merge(T x, T y) {
        if (x.tl == -1) return y;
        if (y.tl == -1) return x;
        T ans;
        ans.sum = x.sum + y.sum;
        ans.tl = x.tl;
        ans.tr = y.tr;
        return ans;
    }
 
public:
 
    void build(vector<int64_t> &arr, int64_t dum, int64_t tl, int64_t tr) {
        if (tl == tr) {
            vec[dum].sum = arr[tl];
            vec[dum].tl = vec[dum].tr = tl;
            return;
        }
        build(arr, 2 * dum + 1, tl, (tl + tr) / 2);
        build(arr, 2 * dum + 2, (tl + tr) / 2 + 1, tr);
        vec[dum] = merge(vec[2 * dum + 1], vec[2 * dum + 2]);
    }
 
    T INF;
 
    void upd(int64_t dum, int64_t tl, int64_t tr, int64_t l, int64_t r) {
        assert(vec[dum].tl == tl && vec[dum].tr == tr);
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += tl - l;
            incLater[dum]++;
            vec[dum].sum += ((tl - l + 1) + (tr - l + 1)) * (tr - tl + 1) / 2;
            return;
        }
        push(dum);
        int64_t mid = (tl + tr) >> 1;
        upd(2 * dum + 1, tl, mid, l, r);
        upd(2 * dum + 2, mid + 1, tr, l, r);
        vec[dum] = merge(vec[2 * dum + 1], vec[2 * dum + 2]);
    }
 
    void upd(int64_t l, int64_t r) {
        upd(0, 0, N - 1, l, r);
    }
 
    T get(int64_t dum, int64_t tl, int64_t tr, int64_t &l, int64_t &r) {
        assert(vec[dum].tl == tl && vec[dum].tr == tr);
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int64_t tm = (tl + tr) >> 1;
        return merge(get(dum * 2 + 1, tl, tm, l, r), get(dum * 2 + 2, tm + 1, tr, l, r));
    }
 
    T get(int64_t l, int64_t r) {
        return get(0, 0, N - 1, l, r);
    }
 
    int64_t N;
 
    SegmentTree(int64_t n) {
        INF.tl = -1;
        n = N = (1 << (int64_t) ceil(log2(n)));
        vec.resize(2 * n);
        addLater.resize(2 * n);
        incLater.resize(2 * n);
    }
 
    void print () {
        for (int64_t i = 0; i < N; i++) {
            cout << get(i, i).sum << ' ';
        }
        cout << '\n';
    }
 
    SegmentTree(int64_t n, vector<int64_t> arr) {
        INF.tl = -1;
        n = N = (1 << (int64_t) ceil(log2(n)));
        while (arr.size() != n) {
            arr.push_back(0);
        }
        vec.resize(2 * n);
        addLater.resize(2 * n);
        incLater.resize(2 * n);
        build(arr, 0, 0, n - 1);
    }
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
        //st.print();
        int64_t t;
        cin >> t;
        if (t == 2) {
            int64_t l, r;
            cin >> l >> r;
            l--, r--;
            cout << st.get(l, r).sum << '\n';
        } else {
            int64_t l, r;
            cin >> l >> r;
            l--, r--;
            st.upd(l, r);
        }
    }
    //cout << st.get(0, N - 1).sum << '\n';
}
