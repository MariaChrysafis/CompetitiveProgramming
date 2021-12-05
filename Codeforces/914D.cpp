#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll int
using namespace std;

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) {
        if (!a || !b) return max(a,b);
        return comb(max(a,b) % min(a,b), min(a,b));
    }
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
    Seg<int> st;
    int n;
    cin >> n;
    st.init(n + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.upd(i, x);
    }
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            //guess
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            if (r - l == 0) {
                cout << "YES\n";
                continue;
            }
            if (st.query(l + 1, r) % x == 0 || st.query(l, r - 1) % x == 0) {
                cout << "YES\n";
                continue;
            }
            if (st.query(l, l) % x != 0) {
                cout << "NO\n";
                continue;
            }
            int left = l;
            int right = r;
            while (left != right) {
                int mid = (left + right + 1)/2;
                if (st.query(l, mid) % x == 0) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            if (left + 2 > r || st.query(left + 2, r) % x == 0) {
                cout << "YES\n";
                continue;
            }
            cout << "NO\n";
        } else {
            int ind; cin >> ind;
            int y; cin >> y;
            st.upd(ind - 1, y);
        }
    }

}
