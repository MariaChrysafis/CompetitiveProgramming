#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#define ll int

using namespace std;

const int MOD = (int) 1e9 + 7;

long long mult(long long x, long long y) {
    return (x * y) % MOD;
}

long long binPow(long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(res, ans);
        }
        res = mult(res, res);
        y >>= 1;
    }
    return ans;
}

long long inv(long long x) {
    return binPow(x, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> fact = {1};
    while(fact.size() != 2 * n + 5) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    cout << mult(mult(fact[2 * n + 2], inv(fact[n + 1])), inv(fact[n + 1])) - 1;
}
