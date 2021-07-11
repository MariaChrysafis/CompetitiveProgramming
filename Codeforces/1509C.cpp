#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>

using namespace std;
vector<long long> arr;
vector<vector<long long>> dp;
const long long INF = LLONG_MAX / 2;

long long memoize(int l, int r) {
    if (l == r) {
        dp[l][r] = 0;
        return dp[l][r];
    } else if (l > r) {
        dp[l][r] = INF;
        return dp[l][r];
    } else if (dp[l][r] != -1) {
        return dp[l][r];
    } else {
        long long pos = INF;
        pos = min(pos, memoize(l + 1, r) + arr[r] - arr[l]);
        pos = min(pos, memoize(l, r - 1) + arr[r] - arr[l]);
        dp[l][r] = pos;
        return pos;
    }
}

int main() {
    int n;
    cin >> n;
    arr.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    cout << memoize(0, n - 1) << endl;
}
