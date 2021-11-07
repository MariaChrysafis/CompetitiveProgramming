#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    freopen("mooomoo.in", "r", stdin);
    freopen("mooomoo.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, B;
    cin >> N >> B;
    vector<int> pos(B);
    vector<int> vec(N), new_vec(N);
    for (int i = 0; i < B; i++) {
        cin >> pos[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    new_vec = vec;
    for (int i = 1; i < N; i++) {
        new_vec[i] = vec[i] - max(vec[i - 1] - 1, 0);
    }
    for (int i: new_vec) {
        //cout << i << ' ';
        if (i < 0) {
            cout << -1;
            return 0;
        }
    }
    vector<int> dp;
    dp.assign(100001, (int)1e9);
    dp[0] = 0;
    for (int i = 0; i < dp.size(); i++) {
        for (int j: pos) {
            if (i - j >= 0) {
                dp[i] = min(dp[i - j] + 1, dp[i]);
            }
        }
    }
    int ans = 0;
    for (int i: new_vec) {
        if (dp[i] == (int)1e9) {
            cout << -1;
            return 0;
        }
        ans += dp[i];
    }
    cout << ans;
}
