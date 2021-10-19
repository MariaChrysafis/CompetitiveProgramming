#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma GCC optimize("O3")


#define ll int

using namespace std;
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return max(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// min on interval [l, r]
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
    int n, m;
    cin >> n >> m;
    Seg<int> st;
    st.init(n + 2);
    int h[n];
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        st.upd(i, h[i]);
    }
    int r[m];
    for (int i = 0; i < m; i++) {
        cin >> r[i];
        if (st.query(0, n - 1) < r[i]) {
            cout << 0 << ' ';
            continue;
        }
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (st.query(left, mid) >= r[i]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        st.upd(left, st.query(left, left) - r[i]);
        cout << left + 1 << " ";
    }
}
