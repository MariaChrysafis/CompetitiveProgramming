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

#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
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
int N, M, K;
vector<signed int> rhymeClass, syllables;
vector<vector<signed int>> dp;
vector<signed int> tot;
void solve() {
    dp.resize(K + 1);
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(N);
    }
    tot.resize(K + 1);
    for (int i = 0; i <= K; i++) {
        tot[i] = 0;
    }
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }
    tot[0] = 1;
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j < rhymeClass.size(); j++) {
            if (i >= syllables[j]) {
                dp[i][rhymeClass[j]] += tot[i - syllables[j]];
                dp[i][rhymeClass[j]] %= MOD;
            }
        }
        for (int j = 0; j < N; j++) {
            tot[i] += dp[i][j];
            tot[i] %= MOD;
        }
    }
}
int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> K;
    rhymeClass.resize(N), syllables.resize(N);
    for (int i = 0; i < N; i++) {
        int s, c;
        cin >> s >> c;
        c--;
        rhymeClass[i] = c;
        syllables[i] = s;
    }
    solve();
    int oc[26];
    for (int i = 0; i < 26; i++) {
        oc[i] = 0;
    }
    for (int i = 0; i < M; i++) {
        char c;
        cin >> c;
        oc[c - 'A']++;
    }
    long long ans = 1;
    for (int c = 0; c < 26; c++) {
        if (oc[c] == 0) {
            continue;
        }
        signed int cntr = 0;
        for (int i = 0; i < N; i++) {
            cntr += binPow (dp[K][i], oc[c]);
            cntr %= MOD;
        }
        ans *= cntr;
        ans %= MOD;
    }
    cout << ans;
}
