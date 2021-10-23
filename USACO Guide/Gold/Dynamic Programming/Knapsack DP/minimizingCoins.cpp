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
const ll MOD = 1e9 + 9;
void print(vector<ll> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    int n, x;
    cin >> n >> x;
    int dp[x + 1];
    for (int i = 0; i <= x; i++) {
        dp[i] = (int)1e9;
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
                dp[i] = min(dp[i], dp[i - v[j]] + 1);
            }
        }
    }
    if (dp[x] == (int)1e9) {
        cout << "-1\n";
        return 0;
    }
    cout << dp[x] << endl;
}
