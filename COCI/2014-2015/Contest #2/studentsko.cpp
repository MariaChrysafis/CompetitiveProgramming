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
int LIS (vector<int> v) {
    int n = v.size();
    Seg<int> st;
    st.init(n + 2);
    vector<int> dp(n);
    set<int> mySet;
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
        mySet.insert(v[i]);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: mySet) {
        myMap[i] = ++cntr;
    }
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
    }
    for (int i = 0; i < n; i++) {
        st.upd(v[i], st.query(0, v[i]) + 1);
    }
    //cout << st.query(0, n) << endl;
    return st.query(0, n);
}
int main() {
    //freopen("inp.txt", "r", stdin);
    //freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    vector<int> vec = v; sort(vec.begin(), vec.end());
    map<int,int> myMap;
    for (int i = 0; i < vec.size(); i++) {
        myMap[vec[i]] = i/K;
    }
    for (int i = 0; i < N; i++) {
        v[i] = myMap[v[i]];
    }
    cout << v.size() - LIS(v);
}
