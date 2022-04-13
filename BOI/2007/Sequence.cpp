#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
 
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
vector<int> arr;
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
Seg<int> st;
int64_t rec (int l, int r) {
    if (l == r) {
        return 0;
    }
    if (l + 1 == r) {
        return max(arr[l], arr[r]);
    }
    int64_t myMax = st.query(l, r);
    int L = l, R = r;
    if (arr[l] == myMax) {
        L = R = l;
    } else if (arr[r] == myMax) {
        L = R = r;
    } else if (arr[(l + r)/2] == myMax) {
        L = R = (l + r)/2;
    }
    while (L != R) {
        int M = (L + R)/2;
        if (st.query(l, M) == myMax) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    int i = max(L, l + 1);
    return rec(l, i - 1) + rec(i, r) + myMax;
    //return dp[l][r];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    arr.resize(n);
    st.init(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        st.upd(i, arr[i]);
    }
    cout << rec(0, n - 1);
}
