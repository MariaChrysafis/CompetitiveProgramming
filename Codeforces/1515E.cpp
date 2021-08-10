#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll MOD;
ll mult(ll a, ll b){
    return (a * b) % MOD;
}
ll binpow(ll a, ll b){
    ll ans = 1;
    ll res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        b /= 2;
        res = mult(res, res);
    }
    return ans;
}
vector<ll> fact, inv_fact;
ll inverse(ll a){
    return binpow(a, MOD - 2);
}
ll binom(ll a, ll b){
    if(a < b) return 0;
    return mult(fact[a], mult(inv_fact[a - b], inv_fact[b]));
}
int main() {
    ll n;
    cin >> n >> MOD;
    vector<vector<ll>> dp(n + 1);
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(dp.size());
        for(int j = 0; j < dp[0].size(); j++){
            dp[i][j] = 0;
        }
    }
    vector<ll> powr = {1};
    inv_fact.resize(n + 1);
    while(powr.size() != n + 1){
        powr.push_back(mult(powr.back(), 2));
    }
    fact = {1};
    while(fact.size() != n + 1){
        fact.push_back(mult(fact.back(), (int)fact.size()));
    }
    inv_fact[n] = inverse(fact[n]);
    for(int i = n - 1; i >= 0; i--){
        //inv_fact[i] i * = inv_fact[i - 1]
        inv_fact[i] = mult(i + 1, inv_fact[i + 1]);
    }
    dp[1][1] = 1;
    dp[1][0] = 0;
    //1111011111
    for(int i = 2; i < dp.size(); i++){
        for(int j = 0; j <= i; j++){
            for(int k = 1; k <= j; k++){
                if(k == j && i == j){
                    dp[i][j] += binpow(2, k - 1);
                    continue;
                }
                if(i - k - 1 >= 0) dp[i][j] += mult(mult(dp[i - k - 1][j - k], binpow(2, k - 1)), binom(j, k));
                if(dp[i][j] > MOD) dp[i][j] -= MOD;
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i <= n; i++){
        ans += dp[n][i];
        ans %= MOD;
    }
    cout << ans << endl;
}
