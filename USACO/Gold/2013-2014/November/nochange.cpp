#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
#define ll long long

int main() {
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int K, N;
    cin >> K >> N;
    vector<ll> coins(K);
    vector<ll> money(N);
    vector<ll> pref = {0};
    for (int i = 0; i < K; i++) {
        cin >> coins[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> money[i];
        pref.push_back(pref.back() + money[i]);
    }
    ll dp[(1 << K)]; //most # candies we can get
    for (int i = 0; i < (1 << K); i++) {
        dp[i] = 0;
    }
    ll myMax = -1;
    for (int i = 1; i < (1 << K); i++) {
        for (int ind = 0; ind < K; ind++) {
            if ((1 << ind) & i) {
                ll l = dp[i - (1 << ind)];
                ll r = N;
                while (l != r) {
                    ll mid = (l + r + 1)/2;
                    if (pref[mid] - pref[dp[i ^ (1 << ind)]] <= coins[ind]) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                dp[i] = max(dp[i], l);
            }
        }
        if (dp[i] == N) {
            ll cntr = 0;
            for (int j = 0; j < K; j++) {
                if (!(i & (1 << j))) {
                    cntr += coins[j];
                }
            }
            myMax = max(myMax, cntr);
        }
    }
    cout << myMax;
}
