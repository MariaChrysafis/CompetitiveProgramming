#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <map>
using namespace std;
int gcd (int x, int y) {
    if (min(x,y) == 0) return max(x,y);
    return gcd(max(x, y) % min(x, y), min(x,y));
}
int lcm (int x, int y) {
    return x/gcd(x, y) * y;
}
const int MOD = 998244353;
long long mult (long long x, long long y) {
    return (x * y) % MOD;
}
vector<long long> fact;
long long binPow (long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult (res, res);
        y /= 2;
    }
    return ans;
}
long long inv (long long x) {
    return binPow(x, MOD - 2);
}
long long combo (long long x, long long y) {
    return mult(fact[x], inv(mult(fact[y], fact[x - y])));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact = {1};
    while (fact.size() <= 100) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    int N, K;
    cin >> N >> K;
    map<int,int> dp[N + 1];
    //dp[i][j] -> number of ways of filling i nodes such that there's an lcm of j
    dp[0][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            for (auto& p: dp[i - j]) {
                dp[i][lcm(p.first, j)] += mult(mult(p.second, combo(N - i + j - 1, j - 1)), fact[j - 1]);
                dp[i][lcm(p.first, j)] %= MOD;
            }
        }
    }
    long long ans = 0;
    for (auto& p: dp[N]) {
        ans += binPow(p.first, K) * p.second;
        ans %= MOD;
    }
    cout << ans;
}
