#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <map>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
ll mult(ll a, ll b){
    if(a * b < MOD) return a * b;
    return (a * b) % MOD;
}
ll sub(ll a, ll b){
    return (a - b + b * MOD) % MOD;
}
ll add(ll a, ll b){
    if(a + b < MOD) return a + b;
    return (a + b) % MOD;
}
ll binpow(ll a, ll b){
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
vector<ll> fact;
vector<ll> fact_inv;
ll inv(ll a){
    return binpow(a, MOD - 2);
}
ll combo(ll a, ll b){
    if(a < b) return 0;
    return mult(fact[a], mult(fact_inv[b], fact_inv[a - b]));
}
void solve(){
    ll n;
    cin >> n;
    vector<long long> v(3 * n + 1);
    v[0] = 1, v[1] = mult(mult(mult(n, (n + 1)), 3), inv(2)), v[2] = 0;
    v[2] = mult(mult(3, mult(n, mult(n, n + 1))), inv(2));
    ll x = inv(3);
    for(int i = 3; i <= 3 * n; i++){
        v[i] = sub(sub(combo(3 * n + 3, i + 1), v[i - 2]) , 3 * v[i - 1]);
        v[i] = mult(v[i], x);
    }
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << v[x] << '\n';
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while(fact.size() != 3e6 + 5){
        fact.push_back(mult(fact.back(), fact.size()));
    }
    fact_inv.resize(fact.size());
    fact_inv[fact_inv.size() - 1] = inv(fact[fact.size() - 1]);
    for(int i = fact_inv.size() - 2; i >= 0; i--){
        fact_inv[i] = mult(fact_inv[i + 1], i + 1);
        //cout << fact_inv[i] << " ";
    }
    //cout << fact_inv[1] << " ";
    solve();
}
