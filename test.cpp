#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<vector<int>> dp, nums;
vector<vector<bool>> marked;
int memoize(int i, int j) {
    if (abs(j - i) <= 1 || j < i) {
        return 0;
    }
    if (marked[i][j]) {
        return dp[i][j];
    }
    int ans = memoize(i + 1, j) + memoize(i, j - 1) - memoize(i + 1, j - 1) + nums[i][j];
    marked[i][j] = true;
    return (dp[i][j] = ans);
}
//const int INF = (int)2e6 + 3;
int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    int oc[n][n + 1];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        //oc[v[i]]++;
    }
    for (int i = 0; i < n; i++) {
        //how many are v[i] up to jth point
        oc[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            oc[i][j] = oc[i][j - 1] + (v[j - 1] == v[i]);
        }
    }
    dp.resize(n), nums.resize(n), marked.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n), nums[i].resize(n), marked[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = nums[i][j] = 0;
            marked[i][j] = false;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            int fnd = -1;
            for (int k = i + 1; k <= j - 1; k++) {
                if (v[i] + v[k] + v[j] == 0) {
                    //nums[i][j]++;
                    fnd = k;
                    break;
                }
            }
            if (fnd == -1) continue;
            nums[i][j] = oc[fnd][j] - oc[fnd][i + 1];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = memoize(i, j);
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << dp[x - 1][y - 1] << '\n';
    }
}
