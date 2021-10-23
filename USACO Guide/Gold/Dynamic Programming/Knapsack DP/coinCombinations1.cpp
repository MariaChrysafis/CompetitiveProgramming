#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
const ll MOD = 1e9 + 7;
int main() {
    int n, x;
    cin >> n >> x;
    ll dp[x + 1];
    for (int i = 0; i <= x; i++) {
        dp[i] = 0;
    }
    dp[0] = 0;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] <= x) {
            dp[v[i]] = 1;
        }
    }
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i - v[j] >= 0 && dp[i - v[j]]) {
                dp[i] += dp[i - v[j]];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[x] << endl;
}
