#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 10;
long long powr(long long a, long long b){
    long long res = 1;
    while(b > 0){
        if(b & 1){
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}
long long inv(long long a){
    return powr(a, MOD - 2);
}
long long modulo(long long x){
    while(x < 0) x += MOD;
    long long y = x % MOD;
    while(y < 0) y += MOD;
}
long long fact[MAX], inv_fact[MAX];
void solve(){
    int n;
    int k;
    cin >> n >> k;
    long long ans = 1;
    for(int i = 1; (k - 1) * (i - 1) + i <= n; i++){
        long long x = (fact[n - (k - 1) * (i - 1)] * inv_fact[n - (k - 1) * (i - 1) - i]) % MOD;
        x *= inv_fact[n];
        x %= MOD;
        ans += (x * fact[n - i]) % MOD;
        ans %= MOD;
    }
    cout << ans % MOD << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact[0] = 1;
    inv_fact[0] = 1;
    for(int i = 1; i < MAX; i++){
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    for(int i = 1; i < MAX; i++){
        inv_fact[i] = inv(fact[i]);
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
