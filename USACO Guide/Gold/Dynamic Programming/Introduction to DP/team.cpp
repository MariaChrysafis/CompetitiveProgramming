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
const ll MOD = 1e9 + 9;
void print(vector<ll> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    int N, M, K;
    cin >> N >> M >> K;
    vector<ll> winner(N), loser(M);
    for (int i = 0; i < N; i++) {
        cin >> winner[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> loser[i];
    }
    ll dp[N + 1][M + 1][K + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = 0ll;
            }
            dp[i][j][0] = 1ll;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = 1; k <= K; k++) {
                dp[i][j][k] = dp[i - 1][j - 1][k - 1] * (winner[i - 1] > loser[j - 1]) + dp[i][j - 1][k] + dp[i - 1][j][k] - dp[i - 1][j - 1][k];
                dp[i][j][k] = (dp[i][j][k] + 3 * MOD) % MOD;
            }
        }
    }
    cout << dp[N][M][K] % MOD;
}
