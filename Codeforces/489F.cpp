#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, MOD;
    cin >> n >> m >> MOD;
    ll prev[n + 1][n + 1], cur[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            prev[i][j] = cur[i][j] = 0;
        }
    }
    //dp[index][# of columns with sum 0][# of columns with sum 1]
    vector<int> col;
    col.assign(n, 0);
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            col[j] += (s[j] == '1');
        }
    }
    int cnt[3]; cnt[0] = cnt[1] = cnt[2] = 0;
    for (int i = 0; i < n; i++) {
        cnt[col[i]]++;
    }
    prev[cnt[0]][cnt[1]] = 1;
    for (ll i = 1; i <= n - m; i++) {
        for (ll j = 0; j <= n; j++) {
            for (ll k = 0; k <= n; k++) {
                if (j + 2 <= n && k - 2 >= 0) cur[j][k] += prev[j + 2][k - 2] * (j + 2) * (j + 1)/2; //[0, 0] -> [1, 1]
                if (k + 2 <= n) cur[j][k] += prev[j][k + 2] * (k + 2) * (k + 1)/2; //[1, 1] -> [2, 2]
                if (j + 1 <= n) cur[j][k] += prev[j + 1][k] * (j + 1) * k; //[0, 1] -> [1, 2]
                if (cur[j][k] > MOD) cur[j][k] %= MOD;
            }
        }
        for (ll j = 0; j <= n; j++) {
            for (ll k = 0; k <= n; k++) {
                prev[j][k] = cur[j][k];
                cur[j][k] = 0;
            }
        }
    }
    cout << prev[0][0] << '\n';
}
