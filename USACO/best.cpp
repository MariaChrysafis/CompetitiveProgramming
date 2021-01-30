#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Problem2TeamBuilding {
public:
  const static int maxN = 1001;
  const static int maxM = 1001;
  const static int maxK = 11;
  int N,M,K;
  long long DP[maxN][maxM][maxK];
  long long FJ[maxN];
  long long FP[maxN];
  long long MOD = 1000000009;
  int fill(){
    for(int fj = 0; fj < N; fj++){
      for(int fp = 0; fp < M; fp++){
        long long counter = 0;
        for(int i = 0; i <= fj; i++){
          for(int j = 0; j <= fp; j++){
            if(FJ[i] > FP[j]){
              counter++;
              if(counter > MOD){
                counter -= MOD;
              }
            }
          }
        }
        DP[fj][fp][1] = counter;
        DP[fj][fp][0] = 0;
      }
    }
    for(int fj = 0; fj < N; fj++) {
      for (int fp = 0; fp < M; fp++) {
        for(int k = 2; k <= K; k++) {
          long long counter = 0;
          for (int i = 1; i <= fj; i++) {
            for (int j = 1; j <= fp; j++) {
              if (FJ[i] > FP[j]) {
                counter += DP[i - 1][j - 1][k - 1];
                if (counter > MOD) {
                  counter -= MOD;
                }
              }
            }
          }
          DP[fj][fp][k] = counter;
        }
      }
    }
    return DP[N - 1][M - 1][K];
  }
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    in >> N >> M >> K;
    for(int i = 0; i < N; i++){
      in >> FJ[i];
    }
    for(int i = 0; i < M; i++){
      in >> FP[i];
    }
    for(int i = 0; i < N; i++){
      for(int j = 0; j < M; j++){
        for(int k = 0; k <= K; k++){
          DP[i][j][k] = -1;
        }
      }
    }
    int x = fill();
    out << x << endl;
  }
};
