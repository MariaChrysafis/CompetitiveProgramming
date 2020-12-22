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
map<int,bool> hv;
bool fine;
int n,m;
void dfs(int x){
  if(adj[x].size() != 2){
    fine = false;
  }
  hv[x] = 1;
  for(int i: adj[x]){
    if(hv[i]) continue;
    dfs(i);
  }
}
void solve(){
  cin >> n >> m;
  int largest = max(n,m) * 2;
  int a1[n + 1];
  int a2[n + 1];
  bool b1[n + 1];
  bool b2[n + 1];
  vector<pair<int,int>> v;
  vector<int> vec;
  for(int i = 0; i < n + 1; i++) a1[i] = a2[i] = b1[i] = b2[i] = 0;
  for(int i = 0; i < m; i++){
    int a,b;
    cin >> a >> b;
    if(a == b) continue;
    a1[a] = i;
    a2[b] = i;
    b1[a] = 1;
    b2[b] = 1;
    v.push_back({a,b});
    adj[a].push_back(largest + i);
    adj[b].push_back(largest + i);
    adj[largest + i].push_back(a);
    adj[largest + i].push_back(b);
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(largest + i);
  }
  int counter = 0;
  for(int i: vec){
    fine = true;
    if(!hv[i]){
      dfs(i);
      if(fine){
        counter++;
      }
    }
  }
  cout << counter + v.size() << endl;
  hv.clear();
  adj.clear();
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
