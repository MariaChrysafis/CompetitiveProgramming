#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;
void print(vector<pair<ll, ll>> v){
    for(pair<ll, ll> p: v){
        cout << p.first << " " << p.second << endl;
    }
}
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve(){
    ll n, p;
    cin >> n >> p;
    vector<ll> fact;
    fact.push_back(1);
    for(int i = 0; i < n; i++){
        fact.push_back((fact.back() * (i + 1)) % p);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ans += (((fact[n + 1 - i] * (n + 1 - i)) % p) * fact[i]);
        ans %= p;
    }
    cout << ans << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
