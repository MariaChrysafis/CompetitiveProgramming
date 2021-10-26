#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
int MAX = 20000;
using namespace std;

#define ll long long 
int MOD;
int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int n;
    cin >> n >> MOD;
    vector<bool> isPrime(MAX);
    for (int i = 0; i < MAX; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    vector<int> primes;
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < MAX; j += i) {
                if (isPrime[j]) {
                    isPrime[j] = false;
                }
            }
        }
    }
    vector<vector<ll>> dp(primes.size() + 1);
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(n + 1);
        for (int j = 0; j < dp[i].size(); j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= primes.size(); i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            ll powr = primes[i - 1];
            while (powr <= n) {
                if (j - powr >= 0) dp[i][j] += dp[i - 1][j - powr] * powr;
                dp[i][j] %= MOD;
                powr *= primes[i - 1];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += dp[primes.size()][i];
        ans %= MOD;
    }
    cout << ans;
}
