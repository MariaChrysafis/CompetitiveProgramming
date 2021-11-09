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
vector<vector<int>> dp;
vector<vector<int>> arr;
int f (int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        return arr[x1][y1];
    }
    return dp[x2 + 1][y2 + 1] - dp[x1][y2 + 1] - dp[x2 + 1][y1] + dp[x1][y1];
}
int bitCount (int x) {
    int cntr = 0;
    for (int i = 0; i <= 16; i++) {
        if (x & (1 << i)) {
            cntr++;
        }
    }
    return cntr;
}
int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    arr.resize(n);
    dp.resize(n + 1);
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(n + 1);
    }
    for (int i = 0; i < n; i++) {
        arr[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i <= n; i++) {
        dp[i][0] = dp[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i - 1][j - 1];
        }
    }
    int myMin = (int)1e9;
    for (int dum = 0; dum < (1 << (n - 1)); dum++) {
        int bc = bitCount(dum);
        if (k - bc < 0) {
            continue;
        }
        vector<int> fences;
        for (int j = 0; j < n - 1; j++) {
            if (dum & (1 << j)) {
                fences.push_back(j);
            }
        }
        vector<pair<int,int>> segments;
        if (!fences.empty()) segments.emplace_back(0,fences[0]);
        for (int j = 1; j < (int)fences.size(); j++) {
            segments.emplace_back(fences[j - 1] + 1, fences[j]);
        }
        if (!fences.empty()) segments.emplace_back(fences.back() + 1, n - 1);
        if (fences.empty()) segments.emplace_back(0, n - 1);
        int DP[n][k - bc + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k - bc; j++) {
                DP[i][j] = (int)1e8;
                if (j == 0) {
                    DP[i][j] = 0;
                    for (pair<int,int> p: segments) {
                        DP[i][j] = max(DP[i][j], f(p.first,0, p.second,i));
                    }
                    continue;
                }
                for (int prev = 0; prev < i; prev++) {
                    int myMax = DP[prev][j - 1];
                    for (pair<int,int> p: segments) {
                        myMax = max(myMax, f(p.first, prev + 1, p.second, i));
                    }
                    DP[i][j] = min(DP[i][j], myMax);
                }
            }
        }
        //cout << dum << " " << DP[0][0] << endl;
        myMin = min(myMin, DP[n - 1][k - bc]);
    }
    cout << myMin;
}
