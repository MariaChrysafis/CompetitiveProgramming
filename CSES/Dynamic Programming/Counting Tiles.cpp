#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
  int N, M;
  cin >> N >> M;
  int64_t dp[(1 << N)][M + 1];
  for (int i = 0; i < (1 << N); i++) {
    for (int j = 0; j <= M; j++) {
      dp[i][j] = 0;
    }
  }
  vector<int> pos[(1 << N)];
  bool okay[(1 << N)];
  for (int i = 0; i < (1 << N); i++) {
    int cntr = 0;
    okay[i] = true;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        if (cntr % 2 == 1) {
          okay[i] = false;
        }
        cntr = 0;
      } else {
        cntr++;
      }
    }
    if (cntr % 2 == 1) {
      okay[i] = false;
    }
  }
  for (int cur = 0; cur < (1 << N); cur++) {
    for (int prev = 0; prev < (1 << N); prev++) {
      if (prev & cur) continue;
      if (okay[cur | prev]) {
        pos[cur].push_back(prev);
      }
    }
  }
  dp[(1 << N) - 1][0] = 1;
  for (int m = 1; m <= M; m++) {
    for (int cur = 0; cur < (1 << N); cur++) {
      for (int prev : pos[cur]) {
        dp[cur][m] += dp[prev][m - 1];
        if (dp[cur][m] > MOD) dp[cur][m] -= MOD;
      }
    }
  }
  int64_t ans = 0;
  for (int i = 0; i < (1 << N); i++) {
    if (okay[i]) ans += dp[i][M];
    ans %= MOD;
  }
  cout << ans;
}
