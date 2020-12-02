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
#define input freopen("barnpainting.in", "r", stdin); freopen("barnpainting.out", "w", stdout);
const long long MOD = pow(10,9) + 7;
using namespace std;
map<int,vector<int>> adj;
vector<int> fix;
vector<int> clear(vector<int> v){
  REP(i,v.size()){
    v[i] = -1;
  }
  return v;
}
vector<vector<int>> dp;
long long dfs(int cur, int prev, int col){
  if(fix[cur] != col && fix[cur] != -1){
    return 0;
  }
  if(dp[cur][col] != -1){
    return dp[cur][col];
  }
  long long prod = 1;
  trav(i,adj[cur]){
    if(i == prev) continue;
    long long sum = 0;
    REP(c,3){
      if(c == col) continue;
      sum += dfs(i,cur,c);
      sum %= MOD;
    }
    prod *= sum;
    prod %= MOD;
  }
  dp[cur][col] = prod;
  return prod;
}
int main(){
  IO
  input
  long long N,K;
  cin >> N >> K;
  fix.resize(N);
  REP(i,N - 1){
    long long u,v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  fix = clear(fix);
  REP(i,K){
    long long a,b;
    cin >> a >> b;
    a--;
    b--;
    fix[a] = b;
  }
  dp.resize(N);
  REP(i,N){
    dp[i].resize(3);
    dp[i] = clear(dp[i]);
  }
  long long x = dfs(0,-1,0) + dfs(0,-1,1) + dfs(0,-1,2);
  x %= MOD;
  cout << x << endl;
}
