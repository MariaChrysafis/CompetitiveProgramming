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
    ll H, W;
    cin >> W >> H;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ll w, h;
    cin >> w >> h;
    ll a1 = ans(W, H, x1, y1, x2, y2, w, h);
    //cout << a1 << endl;
    ll a2 = ans(W, H, W - x2, y1, W - x1, y2, w, h);
    ll a3 = ans(W, H, x1, H - y2, x2, H - y1, w, h);
    ll a4 = ans(W, H, W - x2, H - y2, W - x1, H - y1, w, h);
    a1 = min(min(a1, a2), min(a3, a4));
    if(a1 == 1e9){
        cout << "-1\n";
    }else{
        cout << a1 << '\n';
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
