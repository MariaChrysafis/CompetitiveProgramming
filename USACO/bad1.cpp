#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class Problem2TeamBuilding {
public:
  const static int maxN = 101;
  const static int maxM = 101;
  const static int maxK = 11;
  int N, M, K;
  long long DP[maxN][maxM][maxK];
  long long FJ[maxN];
  long long FP[maxN];
  long long MOD = 1000000009;
  int fill() {
    DP[0][0][1] = (FJ[0] > FP[0]);
    for (int k = 2; k <= K; k++) {
      DP[0][0][k] = 1;
    }
    for (int fj = 1; fj < N; fj++) {
      DP[fj][0][1] = DP[fj - 1][0][1] + (FJ[fj] > FP[0]);
      for (int k = 2; k <= K; k++) {
        DP[fj][0][k] = 0;
      }
    }
    for (int fp = 1; fp < M; fp++) {
      DP[0][fp][1] = DP[fp - 1][0][1] + (FJ[0] > FP[fp]);
      for (int k = 2; k <= K; k++) {
        DP[0][fp][k] = 0;
      }
    }
    for (int fj = 0; fj < N; fj++) {
      for (int fp = 0; fp < M; fp++) {
        DP[fj][fp][0] = 1;
      }
    }
    for (int fj = 1; fj < N; fj++) {
      for (int fp = 1; fp < M; fp++) {
        for (int k = 1; k <= K; k++) {
          if (FP[fp] >= FJ[fj]) {
            DP[fj][fp][k] = DP[fj][fp - 1][k];
            continue;
          }
          int num = fp - k + 2;
          DP[fj][fp][k] = DP[fj - 1][fp][k] + DP[fj - 1][fp][k - 1] * num;
        }
      }
    }
    return DP[N - 1][M - 1][K];
  }
  void solve(std::istream &in, std::ostream &out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    in >> N >> M >> K;
    for (int i = 0; i < N; i++) {
      in >> FJ[i];
    }
    for (int i = 0; i < M; i++) {
      in >> FP[i];
    }
    sort(FJ, FJ + N);
    sort(FP, FP + M);
    long long x = fill();
    out << x << endl;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k <= K; k++) {
          out << i << " " << j << " " << k << " " << DP[i][j][k] << endl;
        }
      }
    }
  }
};
