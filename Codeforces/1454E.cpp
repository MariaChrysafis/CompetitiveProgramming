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
using namespace std;
map<int,vector<int>> adj;
map<int,bool> hasVisited;
pair<int,int> cycle = {-1,-1};
pair<int,int> Null = {-1,-1};
vector<int> cyc;
vector<int> parents;
map<int,bool> init;
long long cntr = 0;
void clear(){
  adj.clear();
  cycle = Null;
  cyc.clear();
  parents.clear();
  hasVisited.clear();
  init.clear();
}
void dfs1(int u, int prev){
  //finds two elements in a cycle
  if(cycle != Null) return;
  hasVisited[u] = 1;
  for(int v: adj[u]){
    if(v == prev || cycle != Null) continue;
    if(hasVisited[v]){
      cycle = {u,v};
      //cout << u << "111" << v << endl;
      return;
    }else{
      dfs1(v,u);
    }
  }
}
void dfs2(int u, int prev){
  //finds the parents
  parents[u] = prev;
  for(int v: adj[u]){
    if(make_pair(u,v) == cycle || make_pair(v,u) == cycle) continue;
    if(v == prev) continue;
    dfs2(v,u);
  }
}
void dfs3(int cur, int prev){
  cntr++;
  for(int i: adj[cur]){
    if(i == prev || init[i]) continue;
    dfs3(i,cur);
  }
}
void solve(){
  clear();
  int n;
  cin >> n;
  parents.resize(n);
  for(int i = 0; i < n; i++){
    int u,v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(0,-1);
  dfs2(cycle.first,-1);
  //cout << cycle.first << " " << cycle.second << endl;
  //return;
  int dum = cycle.second;
  while(dum != cycle.first){
    cyc.push_back(dum);
    dum = parents[dum];
  }
  cyc.push_back(cycle.first);
  for(int i: cyc) init[i] = true;
  long long ans = 0;
  for(int i: cyc){
    cntr = 0;
    dfs3(i,-1);
    ans += cntr * (cntr - 1)/2 + cntr * (n - cntr);
  }
  cout << ans << endl;
  return;
  //cout << "HELLO" << endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
