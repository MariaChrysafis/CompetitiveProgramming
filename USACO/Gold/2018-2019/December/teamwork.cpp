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
#define input freopen("teamwork.in", "r", stdin); freopen("teamwork.out", "w", stdout);
using namespace std;
int main(){
  input
  int N,K;
  cin >> N >> K;
  int arr[N];
  for(int i = 0; i < N; i++){
    cin >> arr[i];
  }
  int interval[N];
  interval[0] = arr[0];
  for(int i = 1; i < N; i++){
    interval[i] = max(arr[i],interval[i - 1]);
  }
  int dp[N];
  for(int i = 0; i < N; i++) dp[i] = -1000000;
  int myMax = 0;
  for(int i = 0; i < K; i++){
    dp[i] = interval[i] * (i + 1);
  }
  for(int i = K; i < N; i++){
    int d = 0;
    for(int j = 1; j <= K; j++){
      d = max(d,arr[i - j + 1]);
      dp[i] = max(dp[i], dp[i - j] + d * j);
    }
  }
  for(int i = 0; i < N; i++){
    myMax = max(myMax,dp[i]);
  }
  cout << myMax << endl;
  return 0;
}
