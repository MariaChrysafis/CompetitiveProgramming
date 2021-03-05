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
#include <cmath>
//#include <multiset>
using namespace std;
vector<int> arr;
vector<vector<int>> dp;
vector<vector<int>> pref;
vector<int> ap;
const int MAX = 2 * pow(10,6);
int rng(int l, int r, int x) {
  x = ap[x + MAX];
  if (x == -1 || r < l) {
    return 0;
  }
  int pl;
  if (l == 0) {
    pl = 0;
  }
  else {
    pl = pref[l - 1][x];
  }
  return pref[r][x] - pl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("threesum.in","r",stdin);
  freopen("threesum.out","w",stdout);
  int N, Q;
  cin >> N >> Q;
  arr.resize(N);
  dp.resize(N);
  ap.resize(2 * MAX);
  for(int i = 0; i < 2 * MAX; i++){
    ap[i] = -1;
  }
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
    dp[i].resize(N);
  }
  pref.resize(arr.size());
  for (int i = 0; i < arr.size(); i++) {
    pref[i].resize(arr.size());
  }
  for (int i = 0; i < arr.size(); i++) {
    ap[arr[i] + MAX] = i;
  }
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
  int a, b;
  while (Q--) {
    cin >> a >> b;
    cout << dp[a - 1][b - 1] << '\n';
  }
}
