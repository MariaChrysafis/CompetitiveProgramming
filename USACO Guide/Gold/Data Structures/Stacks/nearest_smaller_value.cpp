#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#define ll int
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    set<int> s; //set for coordinate compression
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    map<int,int> myMap; //maps old point to new point
    int cntr = 0;
    for (int i : s) {
        myMap[i] = ++cntr; //remap the "coordinates"
    }
    for (int i = 0; i < n; i++) {
        arr[i] = myMap[arr[i]];
    }
    Seg<int> st;
    st.init(n + 3);
    int myMin = (int)1e9;
    for (int i = 0; i < n; i++) {
        myMin = min(myMin, arr[i]);
        st.upd(arr[i], i);
        if (arr[i] == myMin) {
            cout << 0 << ' ';
        } else {
            cout << st.query(0, arr[i] - 1) + 1 << ' ';
        }
    }
}
