#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
  int n, k;
  cin >> n >> k;
  if (n <= 2) {
    cout << 1;
    return 0;
  }
  int64_t dp[n + 1][n * (n - 1) / 2 + 1];
  int64_t prev[n * (n - 1) / 2 + 1];
  int64_t cur[n * (n - 1) / 2 + 1];
  for (int i = 0; i <= n * (n - 1) / 2; i++) {
    prev[i] = 0, cur[i] = 0;
  }
  prev[0] = 1;
  cur[0] = cur[1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= n * (n - 1) / 2; j++) {
      if (i * (i - 1) / 2 < j) {
        cur[j] = 0;
        continue;
      }
      if (j == 0 || j == i * (i - 1) / 2) {
        cur[j] = 1;
        continue;
      }
      cur[j] = prev[j] + cur[j - 1];
      if (j - i >= 0) cur[j] -= prev[j - i];
      cur[j] += MOD, cur[j] %= MOD;
    }
    for (int j = 0; j <= n * (n - 1) / 2; j++) {
      prev[j] = cur[j];
      cur[j] = 0;
    }
  }
  cout << prev[k];
}
