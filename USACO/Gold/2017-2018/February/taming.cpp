#include <cmath>
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
int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    int cost[N][N];
    for (int i = 0; i < N; i++) {
        cost[i][i] = !(arr[i] == 0);
        for (int j = i + 1; j < N; j++) {
            cost[i][j] = cost[i][j - 1] + !(arr[j] == (j - i));
        }
    }
    int dp[N][N + 1];
    for (int i = 0; i < N; i++) {
        dp[i][0] = cost[0][i];
        for (int chng = 1; chng <= N; chng++) {
            dp[i][chng] = (int)1e9;
            for (int j = 0; j < i; j++) {
                dp[i][chng] = min(dp[i][chng], dp[j][chng - 1] + cost[j + 1][i]);
            }
        }
    }
    for (int chng = 0; chng < N; chng++) {
        cout << dp[N - 1][chng] << endl;
    }
}
