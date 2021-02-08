/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>
using namespace std;
class Problem2PalindromicPaths {
public:
  const long long MOD = 1000000007;
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    char arr[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        in >> arr[i][j];
      }
    }
    vector<vector<long long>> prev;
    vector<vector<long long>> cur;
    prev.resize(n);
    cur.resize(n);
    for (int i = 0; i < n; i++) {
      prev[i].resize(n);
      cur[i].resize(n);
    }
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        prev[j][k] = 0;
      }
    }
    for (int i = 0; i < n; i++) {
      prev[i][i] = 1;
    }
    for (int d = 1; d < n; d++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          int row1 = i;
          int col1 = -d + n - 1 - i;
          int row2 = j;
          int col2 = d + n - 1 - j;
          cur[i][j] = 0;
          if (col2 >= n || col1 < 0) {
            continue;
          }
          if (arr[row1][col1] != arr[row2][col2]) {
            continue;
          }
          cur[i][j] = 0;
          if (i + 1 < n) {
            cur[i][j] += prev[i + 1][j];
          }
          if (j > 0) {
            cur[i][j] += prev[i][j - 1];
          }
          if (i + 1 < n && j > 0) {
            cur[i][j] += prev[i + 1][j - 1];
          }
          cur[i][j] += prev[i][j];
          cur[i][j] %= MOD;
        }
      }
      prev = cur;
    }
    out << cur[0][n - 1] << endl;
  }
};


int main() {
	Problem2PalindromicPaths solver;
	std::ifstream in("palpath.in");
	std::ofstream out("palpath.out");
	solver.solve(in, out);
	return 0;
}
