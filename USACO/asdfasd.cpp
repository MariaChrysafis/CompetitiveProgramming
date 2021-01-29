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
  const int INF = 100000000;
  const static int MAX = 100000;
  int DP[26][MAX];
  int pref[26][MAX];
  void fill1(){
    for(int i = 0; i < M; i++){
      pref[i][0] = mat[arr[0]][i];
      for(int j = 1; j < N; j++){
        pref[i][j] = pref[i][j - 1] + mat[arr[j]][i];
      }
    }
  }
  int interval(int a, int b, int c){
    if(b < a){
      return 0;
    }
    if(a == 0){
      return pref[c][b];
    }
    return pref[c][b] - pref[c][a - 1];
  }
  int fill(){
    int soFarMin[N];
    for(int i = 0; i < N; i++){
      soFarMin[i] = INF;
    }
    for(int i = 0; i < N; i++){
      int a;
      if(i >= 1) a = soFarMin[i - 1];
      else a = 0;
      for(int x = i + K - 1; x < min(i + 2 * K - 1,N); x++){
        for(int ch = 0; ch < M; ch++){
          DP[ch][x] = min(DP[ch][x],interval(i,x,ch) + a);
          soFarMin[x] = min(soFarMin[x],DP[ch][x]);
        }
      }
    }
    int ans = INF;
    for(int i = 0; i < M; i++){
      ans = min(ans,DP[i][N - 1]);
    }
    return ans;
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
    for (int k = 0; k < M; k++) {
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
          if (fw[i][k] + fw[k][j] < fw[i][j])
            fw[i][j] = fw[i][k] + fw[k][j];
        }
      }
    }
    for(int i = 0; i < M; i++){
      for(int j = 0; j < N; j++){
        DP[i][j] = INF;
      }
    }
    mat = fw;
    arr.resize(N);
    for(int i = 0; i < N; i++){
      arr[i] = to_int(s[i]);
    }
    fill1();
    int x = fill();
    out << x << endl;
  }
};
