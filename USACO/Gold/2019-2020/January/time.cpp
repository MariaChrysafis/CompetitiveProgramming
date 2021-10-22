#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int N, M, C;
    cin >> N >> M >> C;
    vector<int> val(N);
    for (int i = 0; i < N; i++) {
        cin >> val[i];
    }
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].push_back(u);
    }
    int dp[N][2000];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2000; j++) {
            dp[i][j] = -(int)1e9;
        }
    }
    dp[0][0] = 0;
    int myMax = 0;
    for (int k = 1; k < 2000; k++) {
        for (int i = 0; i < N; i++) {
            for (int j: adj[i]) {
                dp[i][k] = max(dp[i][k], dp[j][k - 1] + val[i]);
                if (i == 0) {
                    myMax = max(myMax, dp[i][k] - C * k * k);
                }
            }
        }
    }
    cout << myMax;
}
