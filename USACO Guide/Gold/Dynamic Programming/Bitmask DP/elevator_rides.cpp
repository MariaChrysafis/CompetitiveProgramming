#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    pair<int,int> dp[(1 << n)];
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = {(int)1e9, (int)1e9};
    }
    dp[0] = {0, m};
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                if (dp[i - (1 << j)].second + arr[j] <= m) {
                    pair<int,int> pos = dp[i - (1 << j)];
                    pos.second += arr[j];
                    dp[i] = min(dp[i], pos);
                } else {
                    pair<int,int> pos = dp[i - (1 << j)];
                    pos.second = min(pos.second, arr[j]);
                    pos.first++;
                    dp[i] = min(dp[i], pos);
                }
            }
        }
    }
    cout << dp[(1 << n) - 1].first;
}
