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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int oc[5001];
    for (int i = 0; i < 5001; i++) {
        oc[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        oc[a[i]]++;
    }
    int dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        int XOR = a[i];
        int cnt[5001];
        for (int j = 0; j < 5001; j++) {
            cnt[j] = 0;
        }
        cnt[a[i]]++;
        set<int> bad;
        if (cnt[a[i]] != oc[a[i]]) {
            bad.insert(a[i]);
        }
        for (int j = i - 1; j >= 0; j--) {
            if (bad.empty()) {
                dp[i] = max(dp[i], dp[j] + XOR);
            }
            if (!cnt[a[j]]) {
                XOR ^= a[j];
            }
            cnt[a[j]]++;
            if (cnt[a[j]] != oc[a[j]]) {
                bad.insert(a[j]);
            } else {
                if (bad.count(a[j])) {
                    bad.erase(a[j]);
                }
            }
        }
    }
    cout << dp[n];
}
