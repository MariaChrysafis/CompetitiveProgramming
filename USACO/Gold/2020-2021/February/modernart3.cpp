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
int dp[300][300];
vector<int> colors;
set<int> positions[301];
int memoize (int l, int r) {
    if (dp[l][r] != (int)1e8) {
        return dp[l][r];
    }
    if (l > r) {
        return 0;
    }
    if (l == r) {
        return (dp[l][r] = 1);
    }
    if (l + 1 == r) {
        return (dp[l][r] = (colors[l] != colors[r]) + 1);
    }
    for (int k = l; k <= r - 1; k++) {
        dp[l][r] = min(dp[l][r], memoize(l, k) + memoize(k + 1, r) - (colors[l] == colors[r] && colors[k] == colors[r]));
    }
    return dp[l][r];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    colors.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> colors[i];
    }
    int prev = -1;
    vector<int> v;
    for (int i = 0; i < N; i++) {
        if (colors[i] != prev) {
            v.push_back(colors[i]);
            prev = colors[i];
        }
    }
    colors = v;
    for (int i = 0; i < colors.size(); i++) {
        positions[colors[i]].insert(i);
    }
    N = colors.size();
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            dp[i][j] = (int)1e8;
        }
    }
    cout << memoize(0, N - 1) << endl;
}
