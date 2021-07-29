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
    int n;
    cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    ll myMax = 0;
    for(int i = 0; i < n - 1; i++){
        myMax = max(myMax, v[i] * v[i + 1]);
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
