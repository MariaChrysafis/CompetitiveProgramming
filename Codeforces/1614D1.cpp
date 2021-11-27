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
ll gcd (ll x, ll y) {
    if (min(x,y) == 0) return max(x,y);
    return gcd(max(x,y) % min(x,y), min(x,y));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> dp;
    dp.assign(5000001, 0);
    vector<ll> oc(dp.size());
    oc.assign(dp.size(), 0);
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        oc[a[i]]++;
        g = gcd(g, a[i]);
    }
    vector<ll> sum;
    sum.assign(dp.size(), 0);
    for (int i = 1; i < dp.size(); i++) {
        for (int j = i; j < dp.size(); j += i) {
            sum[i] += oc[j];
        }
    }
    for (int i = dp.size() - 1; i >= 1; i--) {
        dp[i] = sum[i] * i;
        if (dp[i] == 0) {
            continue;
        }
        for (int j = 2 * i; j < dp.size(); j += i) {
            dp[i] = max(dp[j] + (sum[i] - sum[j]) * i, dp[i]);
        }
    }
    cout << dp[g];
}
