#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
long long binPow (long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
long long inv (long long x) {
    return binPow(x, MOD - 2);
}
vector<long long> fact = {1};
ll combo (ll x, ll y) {
    if (y == 0) return 1;
    if (x < y) return 0;
    return (fact[x] * inv((fact[x - y] * fact[y]) % MOD)) % MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    long long ans = 1;
    vector<long long> arr(N);
    vector<long long> moves(K + 1);
    moves.assign(K + 1, 0);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    while (fact.size() != (int)2e5 + 1) {
        fact.push_back((fact.size() * fact.back()) % MOD);
    }
    for (int k = 1; k <= K; k++) {
        moves[k] = 1;
        for (int i = 0; i < N; i++) {
            moves[k] *= combo(arr[i] + k - 1, k - 1);
            moves[k] %= MOD;
        }
    }
    long long delta = 0;
    for (int i = 0; i < moves.size() - 1; i++) {
        delta += (long long)pow(-1, i % 2) * (moves[i] * combo(K, i)) % MOD;
        delta += MOD;
        delta %= MOD;
    }
    cout << (moves.back() + delta) % MOD;
}
