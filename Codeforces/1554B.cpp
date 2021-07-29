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
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v){
    for(vector<ll> vec: v) print(vec);
    cout << endl;
}
void solve(){
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> v[i + 1];
    }
    ll myMax = -1e9;
    for(ll i = n - k - 2; i <= n; i++){
        for(ll j = i - k - 1; j <= n; j++){
            if(i <= 0 || j <= 0 || i >= j) continue;
            myMax = max(i * j - k * (v[i] | v[j]), myMax);
        }
    }
    cout << myMax << endl;
}
 
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
