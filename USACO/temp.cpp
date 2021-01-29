
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
  const int INF = 1000000;
  const static int MAX = 10000;
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
  int fill(int ch,int x){
    if(x < 0){
      return 0;
    }
    if(DP[ch][x] != INF){
      return DP[ch][x];
    }
    int ans = INF;
    for(int c = 0; c < M; c++){
      for(int i = x - K + 1; i >= 0; i--){
        ans = min(ans,interval(i,x,ch) + fill(c,i - 1));
      }
    }
    DP[ch][x] = ans;
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
    int x = INF;
    for(int i = 0; i < M; i++){
      x = min(fill(i,N - 1),x);
    }
    out << x << endl;
  }
};
