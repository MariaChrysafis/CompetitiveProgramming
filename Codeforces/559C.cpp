#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

ll mult (ll x, ll y) {
    x %= MOD, y %= MOD;
    return (x * y) % MOD;
}

ll binPow (ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}

ll inv (ll x) {
    return binPow(x, MOD - 2);
}

vector<ll> fact;

void sieve () {
    fact = {1};
    while (fact.size() != 2e5 + 10) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
}

ll combo (ll x, ll y) {
    if (x <= y) return (x == y);
    return mult(fact[x], inv(mult(fact[y], fact[x - y])));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int H, W, N;
    cin >> H >> W >> N;
    pair<int,int> black_squares[N];
    for (int i = 0; i < N; i++) {
        cin >> black_squares[i].first >> black_squares[i].second;
        black_squares[i].first--, black_squares[i].second--;
    }
    sort(black_squares, black_squares + N);
    ll dp[N];
    dp[0] = combo(black_squares[0].first + black_squares[0].second, black_squares[0].first);
    for (int i = 1; i < N; i++) {
        dp[i] = 0;
        for (int j = 0; j < i; j++) {
            if (black_squares[j].first <= black_squares[i].first && black_squares[j].second <= black_squares[i].second) {
                int sz1 = abs(black_squares[j].first - black_squares[i].first);
                int sz2 = abs(black_squares[j].second - black_squares[i].second);
                dp[i] += (combo(sz1 + sz2, sz1) * dp[j]) % MOD;
                dp[i] %= MOD;
            }
        }
        dp[i] = (combo(black_squares[i].first + black_squares[i].second, black_squares[i].first) - dp[i] + MOD) % MOD;
    }
    ll bad = 0;
    for (int i = 0; i < N; i++) {
        int sz1 = H - 1 - black_squares[i].first;
        int sz2 = W - 1 - black_squares[i].second;
        bad += (combo(sz1 + sz2, sz2) * dp[i]) % MOD;
        bad %= MOD;
    }
    cout << (combo(H + W - 2, H - 1) - bad + MOD) % MOD;
}
