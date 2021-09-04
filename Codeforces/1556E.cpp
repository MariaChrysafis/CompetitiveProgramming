#include <iostream>
#include <vector>
#define ll long long
using namespace std;
 
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = -1e18; T comb(T a, T b) { return max(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
    seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {    // min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
template<class T> struct Seg1 { // comb(ID,b) = b
    const T ID = 1e18; T comb(T a, T b) { return min(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
    seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {    // min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
int main(){
    int n, q;
    cin >> n >> q;
    vector<ll> pref = {0};
    vector<ll> a(n);
    vector<ll> b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    for(int i = 0; i < n; i++){
        pref.push_back(pref.back() + b[i] - a[i]);
        //cout << pref.back() << " ";
    }
    Seg<ll> st;
    Seg1<ll> st1;
    st.init(n + 2);
    st1.init(n + 2);
    for(int i = 0; i < n; i++){
        st.upd(i, pref[i]);
        st1.upd(i , pref[i]);
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        ll x = st1.query(l, r);
        //cout << x << endl;
        x -= pref[l - 1];
        //cout << x << endl;
        if(x >= 0 && pref[r] - pref[l - 1] == 0) cout << st.query(l, r) - pref[l - 1] << endl;
        else cout << -1 << endl;
    }
}
