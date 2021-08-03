#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <iomanip>
#include <map>
using namespace std;
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
vector<int> pref_hol;
vector<int> pref_gur;
struct cmp {
    bool operator() (int a, int b) const {
        return (pref_hol[a + 1] - pref_gur[a + 1] > pref_hol[b + 1] - pref_gur[b + 1]);
    }
};
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
    map<int,set<pair<int,int>>> myMap;
    for(int i = 0; i < k; i++){
        //cout << pref_hol[i + 1] << " " << pref_gur[i + 1] << endl;
        //return;
        if(pref_hol[i + 1] > pref_gur[i + 1]){
            dp[i] = 0;
        }else{
            dp[i] = 1;
        }
        segTree.upd(i, dp[i]);
        myMap[dp[i]].insert({pref_hol[i + 1] - pref_gur[i + 1], i});
    }
    //print(dp);
    for(int i = k; i < n; i++){
        dp[i] = 1e9;
    }
    for(int i = k; i < n; i++){
        int left = max(i - k, 0);
        int right = i - 1;
        int x = segTree.query(left, right);
        dp[i] = min(dp[i], x + 1);
        for(pair<int,int> u: myMap[x]){
            if(u.second < left) continue;
            int gur = pref_gur[i + 1] - pref_gur[u.second + 1];
            int hol = pref_hol[i + 1] - pref_hol[u.second + 1];
            if(hol > gur){
                dp[i] = min(dp[i], x);
            }
        }
        myMap[dp[i]].insert({pref_hol[i + 1] - pref_gur[i + 1], i});
        myMap[dp[left]].erase({pref_hol[left + 1] - pref_gur[left + 1], left});
        segTree.upd(i, dp[i]);
    }
    cout << dp.back() << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("redistricting");
    solve();
}
