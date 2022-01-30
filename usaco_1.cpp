#include <cmath>
#include <cassert>
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
typedef int64_t ll;
const int MOD = 1e9 + 7;
ll solve (vector<int> v) {
    ll dp[v.size() + 1][1001];
    for (int i = 0; i <= v.size(); i++) {
        for (int j = 0; j <= 1000; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= v.size(); i++) {
        for (int j = 0; j <= 1000; j++) {
            dp[i][j] = 0;
            for (int a = 0; a <= v[i - 1]; a++) {
                if (a - j >= 0) {
                    dp[i][j] += dp[i - 1][a - j];
                    dp[i][j] %= MOD;
                }
            }
        }
    }
    return dp[v.size()][0];
}
ll solve1 (vector<int> v, int A) {
    ll dp[v.size() + 1][1001];
    ll pref[v.size() + 1][1002];
    for (int i = 0; i <= v.size(); i++) {
        for (int j = 0; j <= 1000; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int j = 0; j <= 1002; j++) {
        if (j == 0) {
            pref[0][j] = 0;
            continue;
        }
        pref[0][j] = 1;
    }
    for (int i = 1; i <= v.size(); i++) {
        int st = 0;
        if (i % 2 == 1) st = A;
        for (int j = st; j <= 1000; j++) {
            dp[i][j] = 0;
            if (v[i - 1] - j >= 0) {
                dp[i][j] = pref[i - 1][v[i - 1] - j + 1];
                dp[i][j] %= MOD;
            }
        }
        for (int j = 0; j <= 1001; j++) {
            pref[i][j] = 0;
        }
        pref[i][0] = 0;
        for (int j = 1; j <= 1001; j++) {
            pref[i][j] = pref[i][j - 1] + dp[i][j - 1];
            pref[i][j] %= MOD;
        }
        //cout << '\n';
    }
    return dp[v.size()][A];
}
bool valid1 (vector<int> v) {
    int A = 0;
    for (int i = 0; i < v.size(); i++) {
        A = v[i] - A;
    }
    if (A < 0) {
        return false;
    }
    int ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans = v[i] - ans;
        if (i % 2 == 0) {
            if (A - ans > 0) {
                return false;
            }
        } else {
            if (ans < 0) {
                return false;
            }
        }
    }
    return true;
}
int cntr = 0;
void construct (vector<int> base, vector<int> v) {
    if (v.size() == base.size()) {
        if (valid1(v) && base.size() % 2 == 1) {
            /*
            for (int i: v) {
                cout << i << ' ';
            }
            cout << '\n';
            */
            cntr++;
        }
        return;
    }
    for (int i = 0; i <= base[v.size()]; i++) {
        vector<int> v1 = v; v1.push_back(i);
        construct(base, v1);
    }
}
int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    if (n % 2 == 0) {
        cout << solve(v) << '\n';
        return 0;
    }
    if (n % 2 == 1) {
        //construct(v, {});
        //cout << cntr << '\n';
        ll ans = 0;
        for (int A = 0; A <= 1000; A++) {
            ans += solve1(v, A);
            ans %= MOD;
        }
        cout << ans << '\n';
        return 0;
    }
    construct(v, {});
    cout << cntr;
}
