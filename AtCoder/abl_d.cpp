#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
 
void print (vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
template<class T> struct SegTree { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return max(a, b); }
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
 
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    int myMax = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        myMax = max(myMax, v[i]);
    }
    SegTree<int> st;
    st.init(myMax + 3);
    int myMax1 = 0;
    for(int i = 0; i < n; i++){
        int left = max(v[i] - k, 0);
        int right = min(v[i] + k, myMax);
        int ans = st.query(left, right) + 1;
        st.upd(v[i], ans);
        //cout << ans << " ";
        myMax1 = max(myMax1, ans);
    }
    cout << myMax1 << endl;
}
 
int main() {
    solve();
}
