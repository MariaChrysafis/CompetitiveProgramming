#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
using namespace std;
const int MOD = (int) 998244353;
ll f (int N, int M) {
    if (M == 0) {
        return 0;
    }
    ll dp[N][M + 1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][1] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][1] += dp[i - 1][j];
            dp[i][1] %= MOD;
        }
        for (int j = 2; j <= M; j++) {
            dp[i][j] = dp[i - 1][j - 1];
            dp[i][j] %= MOD;
        }
    }
    ll ans = 0;
    for (int j = 0; j <= M; j++) {
        ans += dp[N - 1][j];
        ans %= MOD;
    }
    return ans;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //find the size of the largest block
    int N, K;
    cin >> N >> K;
    K--;
    vector<ll> fun(N + 1);
    for (int j = 0; j <= N; j++) {
        fun[j] = f(N, j);
    }
    vector<ll> ways;
    ways.assign(N + 1, 0);
    for (int i = 1; i < ways.size(); i++) {
        ways[i] = fun[i];
        ways[i] -= fun[i - 1];
        ways[i] += MOD, ways[i] %= MOD;
    }
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += (ways[i] * fun[min(K/i,N)]) % MOD;
    }
    ans %= MOD;
    cout << (ans * 2) % MOD;
}
