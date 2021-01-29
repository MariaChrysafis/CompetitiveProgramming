#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class Problem3MoortalCowmbat {
public:
  int N, M, K;
  string s;
  vector<int> arr;
  vector<vector<int>> mat;
  int to_int(char c){
    int x = c - 'a';
    return x;
  }
  char to_char(int x){
    for(char c = 'a'; c <= 'z'; c++){
      if(to_int(c) == x){
        return c;
      }
    }
    return 'a';
  }
  const int INF = 1000000;
  vector<int> DP;
  vector<bool> hv;
  //vector<int> pref;
  int fill(int x){
    if(x < 0){
      return 0;
    }
    if(hv[x]){
      return DP[x];
    }
    for(int c = 0; c < M; c++){
      int cost = 0;
      for(int j = x - K + 2; j <= x; j++){
        if(j < 0){
          continue;
        }
        cost += mat[arr[j]][c];
      }
      for(int i = x - K + 1; i >= 0; i--){
        cost += mat[arr[i]][c];
        DP[x] = min(DP[x],cost + fill(i - 1));
      }
    }
    hv[x] = true;
    return DP[x];
  }
  void solve(std::istream &in, std::ostream &out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> fw;
    in >> N >> M >> K;
    in >> s;
    mat.resize(M);
    for (int i = 0; i < M; i++) {
      mat[i].resize(M);
      for (int j = 0; j < M; j++) {
        in >> mat[i][j];
      }
    }
    fw = mat;
    //Floyd-Warshall
    for (int k = 0; k < M; k++) {
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
          if (fw[i][k] + fw[k][j] < fw[i][j])
            fw[i][j] = fw[i][k] + fw[k][j];
        }
      }
    }
    DP.resize(N);
    hv.resize(N);
    for(int i = 0; i < N; i++){
      DP[i] = INF;
      hv[i] = false;
    }
    mat = fw;
    arr.resize(N);

    for(int i = 0; i < N; i++){
      arr[i] = to_int(s[i]);
    }
    int x = fill(N - 1);
    out << x << endl;
  }
};
