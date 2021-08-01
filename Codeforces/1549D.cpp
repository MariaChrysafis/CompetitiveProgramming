#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <map>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<long long> v){
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
ll gcd(ll a, ll b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
 
ll cl(ll x){
    ll pwr = 1;
    while(pwr < x){
        pwr *= 2;
    }
    return pwr;
}
pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
    return make_pair(p1.first,p2.second);
}
 
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return gcd(a,b); }
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
    int n;
    cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    if(n == 1){
        cout << 1 << '\n';
        return;
    }
    vector<ll> vec(n - 1);
    for(int i = 0; i < n - 1; i++){
        vec[i] = abs(v[i + 1] - v[i]);
    }
    Seg<ll> st;
    st.init(vec.size());
    for(int i = 0; i < n - 1; i++){
        st.upd(i, vec[i]);
    }
    int myMax = 0;
    for(int i = 0; i < n - 1; i++){
        int l = i;
        int r = n - 2;
        int x = i - 1;
        while(l <= r){
            int m = (l + r + 1)/2;
            if(l == r){
                if(st.query(l, m) != 1) x = r;
                break;
            }
            if(st.query(i, m) != 1){
                l = m;
            }else{
                r = m - 1;
            }
        }
        myMax = max(x - i + 2, myMax);
    }
    cout << myMax << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
