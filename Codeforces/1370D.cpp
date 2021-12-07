#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
using namespace std;
vector<ll> v;
ll validOdd (ll myMax) {
    //maximum along odd indices is myMax
    int n = v.size();
    vector<vector<ll>> dp; //maximum number of odd indices
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(2);
    }
    dp[0][0] = 1; dp[0][1] = 0;
    for (int i = 1; i < v.size(); i++) {
        dp[i][0] = dp[i - 1][1] + 1;
        dp[i][1] = dp[i - 1][1];
        if (v[i] <= myMax) {
            dp[i][1] = min(dp[i - 1][0] + 1, dp[i][1]);
        }
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}
ll validEven (ll myMax) {
    int n = v.size();
    vector<vector<ll>> dp; //maximum number of odd indices
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(2);
    }
    dp[0][0] = (v[0] <= myMax); dp[0][1] = 1;
    for (int i = 1; i < v.size(); i++) {
        dp[i][1] = dp[i - 1][0] + 1;
        dp[i][0] = dp[i - 1][0];
        if (v[i] <= myMax) {
            dp[i][0] = max(dp[i][0], dp[i - 1][1] + 1);
        }
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k;
    cin >> n >> k; //k -> size of subseqence
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    ll l = 0;
    ll r = 2e9;
    while (l != r) {
        ll m = (l + r )/2;
        if (validOdd(m) >= k || validEven(m) >= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << endl;
}
