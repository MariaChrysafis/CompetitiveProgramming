/*
   REMINDERS TO SELF:
   - think becore implementing
   - CF likes to troll with long long vs int stuff
   - a crazy person repeats teh same the same result
   - don't create unneeded edge cases
   - nutella
*/
// Created by Maria Chrysafis

/* Include all headers */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <cstdio>
#include <cmath>
#define pb push_back
#define pf push_front
#define ll long long
#define mp make_pair
#define REP(i,a) for(int i = 0; i < a; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
char enemy(char c){
  if(c == 'P') return 'S';
  if(c == 'R') return 'P';
  if(c == 'S') return 'R';
  return '1';
}
char Friend(char c){
  if(c == 'P') return 'R';
  if(c == 'R') return 'S';
  if(c == 'S') return 'P';
  return '1';
}
int max4(int a, int b, int c, int d){
  return max(max(a,b),max(c,d));
}
int max3(int a, int b, int c){
  return max(max(a,b),c);
}
int max2(int a, int b){
  return max(a,b);
}
int main(){
  freopen("hps.in", "r", stdin);
  freopen("hps.out", "w", stdout);
  int N,K;
  cin >> N >> K;
  char arr[N];
  for(int i = 0; i < N; i++){
    cin >> arr[i];
    if(arr[i] == 'H') arr[i] = 'R';
  }
  int dp[K + 1][N + 1][3];
  map<int,char> to_char;
  to_char[0] = 'R';
  to_char[1] = 'P';
  to_char[2] = 'S';
  map<char,int> to_int;
  to_int['R'] = 0;
  to_int['P'] = 1;
  to_int['S'] = 2;
  dp[0][0][0] = dp[0][0][1] = dp[0][0][2] = 0;
  int ans = 0;
  for(int i = 1; i <= N; i++){
    dp[0][i][0] = dp[0][i - 1][0];
    dp[0][i][1] = dp[0][i - 1][1];
    dp[0][i][2] = dp[0][i - 1][2];
    if(arr[i - 1] == 'P') dp[0][i][2]++;
    if(arr[i - 1] == 'R') dp[0][i][1]++;
    if(arr[i - 1] == 'S') dp[0][i][0]++;
    ans = max3(dp[0][i][0],dp[0][i][1],dp[0][i][2]);
  }
  for(int i = 1; i <= K; i++){
    for(int j = 0; j <= N; j++){
      for(int k = 0; k < 3; k++){
        if(j == 0){
          dp[i][j][k] = 0;
          continue;
        }
        int s1 = (k + 1) % 3;
        int s2 = (k + 2) % 3;
        bool b1 = arr[j - 1] == Friend(to_char[k]);
        dp[i][j][k] = dp[i][j - 1][k] + b1;
        dp[i][j][k] = max(dp[i][j][k],dp[i - 1][j][k]);
        bool b2 = arr[j - 1] == Friend(to_char[s1]);
        bool b3 = arr[j - 1] == Friend(to_char[s2]);
        dp[i][j][k] = max(dp[i - 1][j - 1][s1] + b2,dp[i][j][k]);
        dp[i][j][k] = max(dp[i - 1][j - 1][s2] + b3,dp[i][j][k]);
        ans = max(ans,dp[i][j][k]);
      }
    }
  }
  cout << ans << endl;
}
