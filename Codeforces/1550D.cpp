#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
 
#define ll long long
using namespace std;
 
void print(vector<ll> v){
    for(ll x: v) cout << x << " ";
    cout << '\n';
}
 
void print(vector<int> v){
    for(int x: v) cout << x << " ";
    cout << '\n';
}
 
const ll MOD = 1e9 + 7;
const ll MAX = 2e5 + 10;
 
vector<ll> fact;
vector<ll> inv_fact;
 
ll mult(ll x, ll y){
    return (x * y) % MOD;
}
 
ll add(ll x, ll y){
    return (x + y) % MOD;
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
 
ll combo(ll a, ll b){
    if(a < 0 || b < 0) return 0;
    if(a < b) return 0;
    return mult(fact[a], mult(inv_fact[b], inv_fact[a - b]));
}
 
void solve(){
    ll n, l, r;
    cin >> n >> l >> r;
    ll left = min(1 - l, r - n);
    ll ans = 0;
    if(left >= 0){
        ans = add(mult(mult(left, combo(n, n/2)), n % 2 + 1), ans);
    }
    //ll i = left + 1;
    for(int i = left + 1; i <= r; i++){
        ll lft = max(1ll, l + i);
        ll rgt = min(n, r - i);
        if(rgt - lft + 1 >= 0){
            ans = add(combo(rgt - lft + 1, n/2 - (lft - 1)), ans);
            //ans += MOD;
            if(n % 2 == 1) ans = add(combo(rgt - lft + 1, n/2 + 1 - (lft - 1)), ans);
            //ans += MOD;
        }else{
            break;
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while(fact.size() != MAX){
        fact.push_back(mult(fact.back(), fact.size()));
    }
    inv_fact.resize(fact.size());
    inv_fact[fact.size() - 1] = inv(fact.back());
    for(int i = fact.size() - 2; i >= 0; i--){
        inv_fact[i] = mult(inv_fact[i + 1], i + 1);
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
