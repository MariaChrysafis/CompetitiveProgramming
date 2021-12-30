#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

const int MOD = 998244353;

void solve() {
    ll N;
    cin >> N;
    ll arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    ll dp[N];
    for (int i = 0; i < N; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;
    ll pref = arr[0];
    map<ll,ll> myMap;
    for (int i = 1; i < N; i++) {
        dp[i] = 2 * dp[i - 1];
        if (myMap[pref]) {
            dp[i] -= dp[myMap[pref] - 1];
        }
        dp[i] += MOD, dp[i] %= MOD;
        myMap[pref] = i;
        pref += arr[i];
        //cout << dp[i] << ' ' << pref << '\n';
    }
    cout << dp[N - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
