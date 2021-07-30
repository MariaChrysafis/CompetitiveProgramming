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
ll minPizzas(ll x){
    ll myMin = 1e18;
    for(ll i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 10; k++){
                if(6 * i + 8 * j + 10 * k >= x){
                    myMin = min(myMin, 15 * i + 20 * j + 25 * k);
                }
            }
        }
    }
    return myMin;
}
void solve(){
    ll n;
    cin >> n;
    //cout << minPizzas(12) << endl;
    ll myMax = n/10 * 25 + minPizzas(n % 10);
    if(n <= 20 ) myMax = min(myMax, minPizzas(n));
    if(n >= 20) myMax = min((n/10 - 1) * 25 + minPizzas(n % 10 + 10), myMax);
    if(n >= 30) myMax = min((n/10 - 2) * 25 + minPizzas(n % 10 + 20), myMax);
    cout << myMax << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
