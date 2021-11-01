#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll bool
using namespace std;

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 1; T comb(T a, T b) { return (a && b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = seg[2*p] && seg[2*p+1]; }
    void upd(int p, T val) {
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = ra && seg[l++];
            if (r&1) rb = seg[--r] && rb;
        }
        return comb(ra,rb);
    }
};
int n;
Seg<bool> st;
int binSearch (int l, int r) {
    int m = (l + r)/2;
    if (l == r) {
        return l;
    }
    if (st.query(0, m) == 0) {
        return binSearch(0, m);
    } else {
        return binSearch(m + 1, r);
    }
}
int find_mex (int i) {
    return binSearch(0, i);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int m;
    cin >> m;
    st.init(n + 3);
    vector<int> arr(n);
    int ans[n + 2];
    for (int i = 0; i < n + 2; i++) {
        ans[i] = 0;
    }
    for (int i = 0; i <= n + 1; i++) {
        st.upd(i, false);
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < m; i++) {
        if (!ans[arr[i]]) {
            st.upd(arr[i], true);
        }
        ans[arr[i]]++;
    }
    int myMin = 1e9;
    for (int i = 0; i < n; i++) {
        if (i + m > n) {
            continue;
        }
        myMin = min(myMin, find_mex(m + 1));
        if (!ans[arr[i + m]]) st.upd(arr[i + m], true);
        ans[arr[i + m]]++;
        if(ans[arr[i]] == 1) st.upd(arr[i], false);
        ans[arr[i]]--;
    }
    cout << myMin;
}
