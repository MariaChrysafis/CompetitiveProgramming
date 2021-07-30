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
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> pref[3][3];
    for(int i = 0; i < 3; i++){
        //'a' + i
        char cur = 'a' + i;
        for(int j = 0; j < 3; j++){
            //position j % 3
            pref[i][j].resize(n + 1);
            pref[i][j][0] = 0;
            for(int pos = 0; pos < s.length(); pos++){
                pref[i][j][pos + 1] = pref[i][j][pos] + (pos % 3 == j && s[pos] == cur);
            }
            //print(pref[i][j]);
        }
    }
    while(m--){
        int l, r;
        cin >> l >> r;
        int myMax = 0;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    if(i == j || i == k || j == k) continue;
                    int a = pref[0][i][r] - pref[0][i][l - 1];
                    a += pref[1][j][r] - pref[1][j][l - 1];
                    a += pref[2][k][r] - pref[2][k][l - 1];
                    myMax = max(myMax, a);
                }
            }
        }
        cout << r - l - myMax + 1 << endl;
    }
}
int main(){
    solve();
}
