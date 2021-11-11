#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K, M;
    cin >> N >> K >> M;
    vector<ll> task(K);
    vector<ll> pref = {0};
    for (int i = 0; i < K; i++) {
        cin >> task[i];
        //pref.push_back(task[i] + pref.back());
    }
    sort(task.begin(), task.end());
    for (int i = 0; i < K; i++) {
        pref.push_back(task[i] + pref.back());
    }
    pref.push_back(pref.back());
    ll dp[N][2500];
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < 2500; j++) {
            dp[i][j] = (ll)1e17;
            if (i == 0) {
                if (j <= K + 1) {
                    dp[i][j] = pref[j];
                    if (dp[i][j] <= M) {
                        ans = max(ans, j);
                    }
                }
            }
        }
    }
    for (ll i = 1; i < N; i++) {
        for (ll j = 0; j < 2500; j++) {
            for (ll k = 0; k <= K + 1; k++) {
                if (j - k < 0) continue;
                dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + pref[k]);
                if (dp[i][j] <= M) {
                    ans = max(ans, j);
                }
            }
        }
    }
    cout << ans;
}
