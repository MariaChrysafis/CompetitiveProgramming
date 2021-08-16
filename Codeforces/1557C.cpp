#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
vector<ll> fact;
ll mult(ll a, ll b){
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
ll inv(ll x){
    return binPow(x, MOD - 2);
}
ll combo(ll a, ll b){
    if(a < b) return 0;
    if(a == b) return 1;
    return mult(fact[a], inv(mult(fact[a - b], fact[b])));
}
ll solve(){
    ll n, k;
    cin >> n >> k;
    ll ans = 0;
    if(n % 2 == 0) {
        ll alt_sum = binPow(2, n - 1) - 1;
        if (n % 2 == 1) {
            alt_sum = 1;
            for (int i = 0; i <= n; i += 2) {
                alt_sum += combo(n, i);
                alt_sum %= MOD;
            }
        }
        ans = binPow(alt_sum, k);
        for (int i = k - 1; i >= 0; i--) {
            ans += mult(binPow(alt_sum, k - i - 1), binPow(2, n * i));
            ans %= MOD;
        }
        return ans;
    }else{
        for(int i = 0; i <= k; i++) {
            ans += mult(combo(k, i), binPow(2, (n - 1) * i));
            ans %= MOD;
        }
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while(fact.size() != 2e5 + 10){
        fact.push_back(mult(fact.back(), fact.size()));
    }
    int t;
    cin >> t;
    while(t--){
        ll x = solve();
        cout << x << endl;
    }
}
