#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <iomanip>
#include <map>
using namespace std;
void setIO(string s) { // the argument is the filename without the extension
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 1e9; T comb(T a, T b) { return min(a,b); }
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
vector<int> pref_hol;
vector<int> pref_gur;
void solve(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    pref_hol.resize(s.length() + 1), pref_gur.resize(s.length() + 1);
    pref_hol[0] = 0, pref_gur[0] = 0;
    for(int i = 0; i < s.length(); i++){
        pref_hol[i + 1] = pref_hol[i] + (s[i] == 'H');
        pref_gur[i + 1] = pref_gur[i] + (s[i] == 'G');
    }
    //print(pref_hol), print(pref_gur);
    Seg<int> segTree;
    segTree.init(n + 1);
    vector<int> dp(n);
    map<int,vector<int>> myMap;
    dp[0] = (s[0] == 'G');
    myMap[dp[0]].push_back(0);
    segTree.upd(0, dp[0]);
    for(int i = 0; i < k; i++){
        if(pref_hol[i + 1] > pref_gur[i + 1]){
            dp[i] = 0;
        }else{
            dp[i] = 1;
        }
        //dp[i] = (pref_hol[i] >= pref_gur[i]);
    }
    for(int i = k; i < n; i++){
        dp[i] = 1e9;
    }
    //print(dp);
    for(int i = 1; i < n; i++){
        int left = max(i - k, 0);
        int right = i - 1;
        int x = segTree.query(left, right);
        dp[i] = min(dp[i], x + 1);
        for(int u: myMap[x]){
            if(u < left || u > right) continue;
            int gur = pref_gur[i + 1] - pref_gur[u + 1];
            int hol = pref_hol[i + 1] - pref_hol[u + 1];
            if(hol > gur){
                dp[i] = min(dp[i], x);
            }
        }
        myMap[dp[i]].push_back(i);
        segTree.upd(i, dp[i]);
    }
    //print(dp);
    cout << dp.back() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("redistricting");
    solve();
}
