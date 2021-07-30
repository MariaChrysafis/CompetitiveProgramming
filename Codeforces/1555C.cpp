#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void print(vector<bool> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<char> v){
    for(char c: v) cout << c << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v) {
    for (vector<ll> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<char>> v){
    for(vector<char> vec: v) print(vec);
    cout << endl;
}
vector<int> read(int n){
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    return v;
}
vector<ll> readll(int n){
    vector<ll> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    return v;
}
vector<char> readc(int n){
    vector<char> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    return v;
}
vector<int> sorted(vector<int> v){
    sort(v.begin(), v.end());
    return v;
}
vector<ll> sorted(vector<ll> v){
    sort(v.begin(), v.end());
    return v;
}
ll ans (ll W, ll H, ll x1, ll y1, ll x2, ll y2, ll w, ll h){
    ll a1 = 1e9;
    ll dy1 = max(0ll, h - y1);
    ll dx1 = max(0ll, w - x1);
    //cout << dx1 << " " << dy1 << endl;
    if(dy1 + y2 <= H) a1 = dy1;
    if(dx1 + x2 <= W) a1 = min(a1, dx1);
    return a1;
}
void solve(){
    int n;
    cin >> n;
    vector<ll> a[2];
    ll sum[2];
    for(int i = 0; i < 2; i++){
        a[i].resize(n);
        sum[i] = 0;
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
            sum[i] += a[i][j];
        }
        //print(a[i]);
    }
    vector<int> pref(n + 1), suf(n + 1);
    pref[0] = 0;
    for(int i = 0; i < n; i++){
        pref[i + 1] = pref[i] + a[0][i];
    }
    suf[n] = 0;
    for(int i = n - 1; i >= 0; i--){
        suf[i] = suf[i + 1] + a[1][i];
    }
    //print(pref);
    ll ans = 1e10;
    for(int i = 1; i <= n; i++){
        ans = min(ans, max(sum[0] - pref[i], sum[1] - suf[i - 1]));
    }
    cout << ans << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
