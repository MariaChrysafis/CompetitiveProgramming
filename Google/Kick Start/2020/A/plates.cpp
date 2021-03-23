#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<vector<int>> DP;
vector<vector<int>> plates;
int N, K, P;
const int INF = 10000000;
int memoize(int x, int y){
  if(y < 0){
    return -INF;
  }
  if(y == 0){
    return 0;
  }
  if(x == -1){
    return 0;
  }
  if(DP[x][y] != -1){
    return DP[x][y];
  }
  //we're on the xth stack
  int myMax = memoize(x - 1,y);
  int pref = 0;
  for(int i = 0; i < K; i++){
    pref += plates[x][i];
    myMax = max(memoize(x - 1,y - i - 1) + pref, myMax);
  }
  DP[x][y] = myMax;
  return myMax;
}
int solve(){
    cin >> N >> K >> P;
    plates.resize(N);
    for(int i = 0; i < N; i++){
      plates[i].resize(K);
    }
    for(int i = 0; i < N; i++){
      for(int j = 0; j < K; j++){
        cin >> plates[i][j];
      }
    }
    DP.resize(N);
    for(int i = 0; i < N; i++){
      DP[i].resize(P + 1);
      for(int j = 0; j <= P; j++){
        DP[i][j] = -1;
      }
    }
    int x = memoize(N - 1, P);
    return x;
}
int main(){
    int T;
    cin >> T;
    int orig = T;
    while(T--){
      cout << "Case #" << orig - T << ": ";
        int x = solve();
        cout << x << endl;
    }
}
