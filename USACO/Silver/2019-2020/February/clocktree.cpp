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
#define vi vector<int>
#define REP(i,a) for(int i = 0; i < a; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define input freopen("clocktree.in", "r", stdin); freopen("clocktree.out", "w", stdout);
using namespace std;
map<int,vi> adj;
vi arr;
vi depth;
void clear(){
  REP(i,depth.size()){
    depth[i] = -1;
  }
}
void Depth(int cur, int prev, int d){
  depth[cur] = d;
  trav(i,adj[cur]){
    if(i != prev){
      Depth(i,cur,d + 1);
    }
  }
}
int main(){
  input
  int N;
  cin >> N;
  arr.resize(N);
  depth.resize(N);
  REP(i,N){
    cin >> arr[i];
  }
  REP(i,N - 1){
    int u,v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  int ans = 0;
  REP(i,N){
    Depth(i,-1,0);
    int cntr = 0;
    REP(j,N){
      if(depth[j] % 2 == 0){
        cntr += arr[j];
      }else{
        cntr -= arr[j];
      }
    }
    if(cntr < 0){
      cntr -= 12 * cntr;
    }
    cntr %= 12;
    if(cntr == 1 || cntr == 0){
      ans++;
    }
    //cout << cntr << endl;
  }
  cout << ans << endl;
}
