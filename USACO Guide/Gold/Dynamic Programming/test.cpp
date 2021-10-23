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
#define ll long long
vector<vector<ll>> cost;
ll interval (int color, int l, int r) {
    return cost[color][r + 1] - cost[color][l];
}
int main() {
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    int N, M, K;
    cin >> N >> M >> K;
    string s;
    cin >> s;
    vector<vector<ll>> adj(M);
    for (int i = 0; i < M; i++) {
        adj[i].resize(M);
        for (int j = 0; j < M; j++) {
            cin >> adj[i][j];
        }
    }
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
            }
        }
    }
    cost.resize(M);
    for (int i = 0; i < M; i++) {
        cost[i] = {0};
        for (int j = 1; j <= N; j++) {
            cost[i].push_back(cost[i].back() + adj[s[j - 1] - 'a'][i]);
        }
    }
    ll dp[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = (int)1e9;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = K - 1; j < N; j++) {
            dp[i][j] = interval(i, 0, j);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int col1 = 0; col1 < M; col1++) {
            for (int l = K; l <= N; l++) {
                for (int col2 = 0; col2 < M; col2++) {
                    if (i - l < 0) continue;
                    dp[col1][i] = min(dp[col1][i], dp[col2][i - l] + interval(col1, i - l + 1, i));
                }
            }
        }
    }
    //cout << dp[3][K - 1] << endl;
    ll myMin = INT_MAX;
    for (int i = 0; i < M; i++) {
        myMin = min(myMin, dp[i][N - 1]);
        //cout << i << " "<< dp[i][N - 1] << endl;
    }
    cout << myMin;
}
