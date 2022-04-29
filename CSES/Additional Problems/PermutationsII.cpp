#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    int64_t combo[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) combo[i][j] = 1;
            else if (i < j) combo[i][j] = 0;
            else if (j == 0) combo[i][j] = 1;
            else combo[i][j] = (combo[i - 1][j - 1] + combo[i - 1][j]) % MOD;
        }
    }
    vector<int64_t> fact; fact.push_back(1);
    while (fact.size() != n + 1) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    vector<int64_t> powr; powr.push_back(1);
    while (powr.size() != n + 1) {
        powr.push_back((powr.back() * 2) % MOD);
    }
    int64_t ans = fact[n];
    for (int k = 1; k <= n; k++) {
        int64_t cntr = 0;
        for (int t = 1; t <= k; t++) {
            cntr += (((combo[k - 1][t - 1] * combo[n - k][t]) % MOD * fact[n - k]) % MOD * powr[t]) % MOD;
            cntr %= MOD;
        }
        if (k % 2 == 0) ans += cntr;
        else ans += MOD - cntr;
        ans %= MOD;
    }
    cout << ans;
}

/*
Principle of Inclusion Exclusion
*/
