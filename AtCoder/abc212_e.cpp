#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#define ll long long
using namespace std;
const int MOD = 998244353;
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    long long dp[k + 1][n];
    for(int j = 0; j < n; j++){
        adj[j].push_back(j);
        dp[0][j] = 0;
    }
    dp[0][0] = 1;
    long long pref = 1;
    long long new_pref = 0;
    for(int i = 1; i <= k; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = pref;
            for(int dj: adj[j]){
                dp[i][j] += (MOD - dp[i - 1][dj]);
                dp[i][j] %= MOD;
            }
            new_pref += dp[i][j];
            new_pref %= MOD;
        }
        pref = new_pref;
        new_pref = 0;
    }
    cout << dp[k][0] << endl;
}
