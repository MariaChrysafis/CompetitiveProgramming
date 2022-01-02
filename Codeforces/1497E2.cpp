#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
const int MOD = 1e9 + 7;

const int MAX = 1e7 + 1;
vector<int> m(MAX);
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i] = m[v[i]];
    }
    int howFar[n][k + 1];
    map<int,int> rep;
    set<int> ones;
    for (int i = 0; i < n; i++) {
        if (rep[v[i]]) {
            ones.insert(-rep[v[i]] + 1);
        }
        rep[v[i]] = i + 1;
        int cntr = 0;
        for (int j: ones) {
            int ind = -j;
            howFar[i][cntr] = ind + 1;
            cntr++;
            if (cntr > k) {
                break;
            }
        }
        for (int j = cntr; j <= k; j++) {
            howFar[i][j] = 0;
        }
    }
    int dp[n + 1][k + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 1e8;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int prev = 0; prev <= j; prev++) {
                dp[i][j] = min(dp[i][j], dp[howFar[i - 1][prev]][j - prev] + 1);
            }
        }
    }
    cout << dp[n][k] << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    m.resize(MAX);
    for (int i = 0; i < MAX; i++) {
        m[i] = i;
    }
    for (ll i = 2; i < MAX; i++) {
        if (m[i] == i) {
            for (ll j = i * i; j < MAX; j += i * i) {
                while (m[j] % (i * i) == 0) {
                    m[j] /= (i * i);
                }
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
