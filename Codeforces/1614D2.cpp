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
const int sz = 2e7 + 10;
int oc[sz];
ll dp[sz];
ll sum[sz];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < sz; i++) {
        oc[i] = dp[i] = sum[i] = 0;
    }
    int a[n];
    for (int i = 0; i < sz; i++) {
        oc[i] = 0;
    }
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        oc[a[i]]++;
        g = gcd(g, a[i]);
    }
    for (int i = 1; i < sz; i++) {
        if (!sum[i] && !oc[i]) {
            continue;
        }
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                sum[j] += oc[i];
                if (j * j != i) sum[i/j] += oc[i];
            }
        }
    }
    for (int i = sz - 1; i >= 0; i--) {
        if (!sum[i]) {
            continue;
        }
        dp[i] = sum[i] * i;
        for (int j = 2 * i; j < sz; j += i) {
            if (sum[j] != 0) {
                dp[i] = max(dp[j] + (sum[i] - sum[j]) * i, dp[i]);
            }
        }
    }
    cout << dp[g];
}
