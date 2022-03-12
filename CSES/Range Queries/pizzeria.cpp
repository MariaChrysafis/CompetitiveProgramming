#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
 
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 1e18; T comb(T a, T b) { return min(a,b); }
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
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int64_t> v(N);
    Seg<int64_t> st1, st2;
    st1.init(N + 1), st2.init(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        st1.upd(i, v[i] - i);
        st2.upd(i, v[i] + i);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int64_t i, x;
            cin >> i >> x;
            i--;
            v[i] = x;
            st1.upd(i, v[i] - i);
            st2.upd(i, v[i] + i);
        } else {
            int64_t i; cin >> i; i--;
            cout << min(i + st1.query(0, i), -i + st2.query(i + 1, N - 1)) << '\n';
        }
    }
}
