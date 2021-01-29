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
  vector<vector<int>> pref;
  void fill1(){
    for(int i = 0; i < M; i++){
      pref[i][0] = mat[arr[0]][i];
      for(int j = 1; j < N; j++){
        pref[i][j] = pref[i][j - 1] + mat[arr[j]][i];
        cout << pref[i][j] << " ";
      }
      cout << endl;
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
      int val = interval(x - K + 2,x,c);
      cost = val;
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
    pref.resize(26);
    for(int i = 0; i < 26; i++){
      pref[i].resize(N);
    }
    for(int i = 0; i < N; i++){
      arr[i] = to_int(s[i]);
    }
    fill1();
    int x = fill(N - 1);
    out << x << endl;
  }
};
