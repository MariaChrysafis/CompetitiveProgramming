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
void print(pair<int,int> p) {
    cout << p.first << " " << p.second << endl;
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
int points(pair<int,int> p1, pair<int,int> p2){
    int a1 = abs(p1.first - p2.first);
    int b1 = abs(p1.second - p2.second);
    return gcd(a1, b1) + 1;
}
void solve(){
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    map<pair<int,int>,ll> oc;
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
        v[i].first %= 4, v[i].second %= 4;
        oc[v[i]]++;
        //cout << v[i].first << " " << v[i].second << endl;
    }
    cout << endl;
    vector<pair<int,int>> pos;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            pos.push_back({i, j});
        }
    }
    //cout << oc[{0, 0}] << " ";
    ll cntr = 0;
    for(pair<int,int> p1: pos){
        if(oc[p1] >= 3){
            cntr += oc[p1] * (oc[p1] - 1) * (oc[p1] - 2)/6;
        }
    }
    for(pair<int,int> p1: pos) {
        for (pair<int, int> p2: pos) {
            if(p1 == p2) continue;
            if(oc[p1] <= 1 || oc[p2] == 0) continue;
            int a = points(p1, p1) + points(p1, p2) + points(p1, p2);
            if(a % 4 == 3){
                cntr += oc[p1] * (oc[p1] - 1)/2 * oc[p2];
            }
        }
    }
    for(pair<int,int> p1: pos){
        for(pair<int,int> p2: pos){
            for (pair<int,int> p3: pos){
                if(p1 == p2 || p1 == p3 || p2 == p3 || oc[p1] == 0 || oc[p2] == 0 || oc[p3] == 0){
                    continue;
                }
                int a = points(p1, p2) + points(p1, p3) + points(p3, p2);
                if(a % 4 == 3){
                    cntr++;
                }
            }
        }
    }
    cout << cntr << endl;
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
