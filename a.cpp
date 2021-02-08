#include <iostream>
using namespace std;
class Problem2PalindromicPaths {
public:
  const int MOD = 1000000007;
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    char arr[n][n];
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        in >> arr[i][j];
      }
    }
    long long dp[n][n][n];
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        for(int k = 0; k < n; k++){
          dp[i][j][k] = 0;
          if(i == 0 && j == k){
            dp[i][j][j] = 1;
          }
        }
      }
    }
    for(int d = 1; d < n; d++){
      for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
          int row1 = i;
          int col1 = -d + n - 1 - i;
          int row2 = j;
          int col2 = d + n - 1 - j;
          if(col2 >= n || col1 < 0) {
            continue;
          }
          if(arr[row1][col1] != arr[row2][col2]){
            continue;
          }
          if(i + 1 < n) dp[d][i][j] += dp[d - 1][i + 1][j];
          if(j > 0) dp[d][i][j] += dp[d - 1][i][j - 1];
          if(i + 1 < n && j > 0) dp[d][i][j] += dp[d - 1][i + 1][j - 1];
          dp[d][i][j] += dp[d - 1][i][j];
          dp[d][i][j] %= MOD;
        }
      }
    }
    out << dp[n - 1][0][n - 1] << endl;
  }
};
