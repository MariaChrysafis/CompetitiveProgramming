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
const ll MOD = 998244353;
ll mult(ll a, ll b){
    a %= MOD;
    b %= MOD;
    return (a * b) % MOD;
}
ll binPow(ll a, ll b){
    ll ans = 1;
    ll res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        b /= 2;
    }
    return ans;
}
ll inv(ll a){
    return binPow(a, MOD - 2);
}
ll solve(vector<ll> v){
    sort(v.begin(), v.end());
    ll ans = 1;
    ll soFar = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] - 1 - soFar <= 0){
            return 0;
        }
        ans = mult(ans, v[i] - 1 - soFar);
        soFar++;
    }
    return ans;
}
int main() {
    vector<ll> fact;
    fact.push_back(1);
    while(fact.size() != 30){
        fact.push_back(mult(fact.size(), fact.back()));
    }
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> arr(n);
    for(int i = 0; i < n; i++){
        arr[i].resize(m);
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }
    ll ans = 0;
    for(int i = 0; i < m; i++){
        vector<ll> v;
        for(int j = 0; j < n; j++){
            v.push_back(arr[j][i]);
        }
        ans = ans + mult((fact[n] - solve(v) + MOD) % MOD, inv(fact[n]));
        ans %= MOD;
    }
    cout << ans;
}
