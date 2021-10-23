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
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    for (int j = 0; j < n; j++){
        if (v[j] <= x) {
            dp[v[j]] = 1;
        }
        for (int i = 0; i <= x; i++) {
            if (i - v[j] >= 0 && dp[i - v[j]]) {
                dp[i] += dp[i - v[j]];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[x] << endl;
}
