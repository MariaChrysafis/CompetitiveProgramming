#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
//#include <multiset>
using namespace std;
vector<int> arr;
vector<vector<int>> dp;
vector<vector<int>> pref;
unordered_map<int, int> ap;
int rng(int l, int r, int x) {
  x = ap[x];
  if (x == 0 || r < l) {
    return 0;
  }
  x--;
  int pl;
  if (l == 0) {
    pl = 0;
  }
  else {
    pl = pref[l - 1][x];
  }
  return pref[r][x] - pl;
}
void solve() {
  int n = arr.size();
  pref.resize(n);
  for (int i = 0; i < n; i++) {
    pref[i].resize(n);
  }
  for (int i = 0; i < n; i++) {
    ap[arr[i]] = i + 1;
  }
}
int main() {
  freopen("threesum.in","r",stdin);
  freopen("threesum.out","w",stdout);
  int N, Q;
  cin >> N >> Q;
  arr.resize(N);
  dp.resize(N);
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
    dp[i].resize(N);
  }
  solve();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      dp[i][j] = -1;
    }
    pref[0][i] = (arr[0] == arr[i]);
    for (int j = 1; j < N; j++) {
      pref[j][i] = pref[j - 1][i] + (arr[j] == arr[i]);
    }
  }
  for(int x = N - 1; x >= 0; x--){
    for(int y = 0; y < N; y++){
      if(y - x < 2){
        dp[x][y] = 0;
        continue;
      }
      if(y - x == 2){
        dp[x][y] = (arr[x] + arr[x + 1] + arr[x + 2] == 0);
        continue;
      }
      dp[x][y] = dp[x + 1][y] + dp[x][y - 1] - dp[x + 1][y - 1];
      dp[x][y] += rng(x + 1, y - 1, -arr[x] - arr[y]);
    }
  }
  while (Q--) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    cout << dp[a][b] << '\n';
  }
}
