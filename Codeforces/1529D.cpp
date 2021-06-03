#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
const int MOD = 998244353;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    long long div[n + 1];
    long long dp[n + 1];
    for(int i = 0; i <= n; i++){
        div[i] = 0;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 2 * i; j <= n; j += i){
            div[j]++;
        }
    }
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        dp[i] = 2 * dp[i - 1] + div[i];
        dp[i] %= MOD;
    }
    cout << (dp[n] - dp[n - 1] + MOD) % MOD << endl;
}
