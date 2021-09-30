#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#define ll long long

using namespace std;

vector<vector<int>> dp;
vector<vector<int>> arr;

void print(vector<vector<int>> vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[0].size(); j++) {
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void fill_dp() {
    int n = dp.size();
    int m = dp[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = arr[i][j];
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + arr[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + arr[i][j];
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
            }
        }
    }
}

int cells (int x1, int y1, int x2, int y2) {
    if(x1 == 0 && y1 == 0) {
        return dp[x2][y2];
    }
    if(y1 == 0) {
        return dp[x2][y2] - dp[x1 - 1][y2];
    }
    if (x1 == 0) {
        return dp[x2][y2] - dp[x2][y1 - 1];
    }
    return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
}

void solve() {
    int n, m;
    cin >> n >> m;
    dp.resize(n);
    arr.resize(n);
    bool found = false;
    for (int i = 0; i < n; i++) {
        dp[i].resize(m);
        arr[i].resize(m);
        string s;
        cin >> s;
        for (int j = 0; j < m; j++){
            arr[i][j] = (s[j] - '0');
            dp[i][j] = 0;
        }
    }
    fill_dp();
    int myMin = 20;
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < m; y1++) {
            for (int x2 = x1 + 4; x2 < n; x2++) {
                for (int y2 = y1 + 3; y2 < m; y2++) {
                    int cost1 = cells(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
                    if(cost1 > myMin) {
                        break;
                    }
                    int cost2 = cells(x1, y1, x2, y2) - cost1;
                    cost2 -= arr[x1][y1], cost2 -= arr[x1][y2], cost2 -= arr[x2][y1], cost2 -= arr[x2][y2];
                    cost2 = 2 * (x2 - x1 + 1) + 2 * (y2 - y1 + 1) - 8 - cost2;
                    myMin = min(myMin, cost1 + cost2);
                    if(cost2 + cost1 - (x2 - x1 + 1) + 2 > myMin) {
                        break;
                    }
                    if(myMin == 0) {
                        break;
                    }
                }
            }
        }
    }
    cout << myMin << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
