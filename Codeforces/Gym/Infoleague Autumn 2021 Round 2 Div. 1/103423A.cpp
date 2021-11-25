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
const int MOD = 1e9 + 7;
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a+b; }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
int st[20][(int)1e6 + 1];
inline int log2(int x) { return 31 - __builtin_clz(x); }
int query (int l, int r) {
    if (l == r) {
        return st[0][l];
    }
    const int i = log2(r - l + 1);

    return min(st[i][l], st[i][r + 1 - (1 << i)]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Seg<int> segTree;
    segTree.init(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        st[0][i] = v[i];
    }
    for (int i = 1; i < 20; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    vector<int> vec = {};
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (vec.empty() || v[i] <= v[vec.back()]) {
            vec.push_back(i);
            segTree.upd(i, 1);
        }
        if (v[i] > v[vec.back()]) {
            while (!vec.empty() && v[i] > v[vec.back()]) {
                segTree.upd(vec.back(), 0);
                vec.pop_back();
            }
            vec.push_back(i);
            segTree.upd(i, 1);
        }
        int l = i;
        int r = n - 1;
        while (l != r) {
            int m = (l + r)/2;
            if (query(i, m) < v[i]) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if (query(i, n - 1) >= v[i]) {
            l = n;
        }
        if (l == 0) {
            continue;
        }
        ans += segTree.query(0, l - 1);
    }
    cout << ans << '\n';

}
