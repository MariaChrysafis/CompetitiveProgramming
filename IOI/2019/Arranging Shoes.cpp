#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include "shoes.h"
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
using namespace std;
 
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
 
int64_t get_inversions(vector<int> v) {
    Seg<int> st;
    st.init(v.size() + 3);
    int64_t ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans += st.query(v[i] + 1, v.size() + 2);
        st.upd(v[i], st.query(v[i], v[i]) + 1);
    }
    return ans;
}
 
long long count_swaps(vector<int> v) {
    map<int, set<int>> myMap;
    for (int i = 0; i < v.size(); i++) {
        myMap[v[i]].insert(i);
    }
    vector<int> vec(v.size());
    int cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        if (myMap[-v[i]].empty()) continue;
        if (myMap[v[i]].count(i) == false) continue;
        int x = *myMap[-v[i]].begin();
        myMap[-v[i]].erase(x);
        myMap[v[i]].erase(i);
        vec[i] = cntr++;
        vec[x] = cntr++;
        if (v[i] > 0) {
            swap(vec[i], vec[x]);
        }
    }
    return get_inversions(vec);
}
 
/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << count_swaps({-1,1,-1,-1,-1,1,1,1});
}
 
*/
