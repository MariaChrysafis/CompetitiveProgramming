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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;


template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return max(a,b); }
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

void process (vector<int> v) {
    sort(v.begin(), v.end());
    set <int> s;
    for (int i = 0; i < v.size(); i++) {
        if (s.count(v[i] - 1)) {
            s.insert(v[i] - 1);
            continue;
        }
        if (s.count(v[i])) {
            s.insert(v[i]);
            continue;
        }
        s.insert(v[i] + 1);
    }
    cout << s.size() << ' ';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Seg<ll> st;
    st.init(n + 10);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]++;
    }
    process(v);
    sort(v.begin(), v.end());
    vector<ll> dp;
    dp.assign(n + 4, 0);
    for (int i = 0; i < n; i++) {
        dp[v[i] + 1] = max(st.query(0, v[i]) + 1, dp[v[i] + 1]);
        dp[v[i]] = max(st.query(0, v[i] - 1) + 1, dp[v[i]]);
        dp[v[i] - 1] = max(st.query(0, v[i] - 2) + 1, dp[v[i] - 1]);
        st.upd(v[i] + 1, dp[v[i] + 1]);
        st.upd(v[i], dp[v[i]]);
        st.upd(v[i] - 1, dp[v[i] - 1]);
    }
    ll myMax = 0;
    for (int i = 0; i < dp.size(); i++) {
        myMax = max(myMax, dp[i]);
    }
    cout << myMax << '\n';
}
