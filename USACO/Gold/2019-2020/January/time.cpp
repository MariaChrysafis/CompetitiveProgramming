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
#define REP(i,a) for(ll i = 0; i < a; i++)
#define FOR(i,a,b) for(ll i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
const ll maxN = 1001;
const ll maxC = 1001;
const ll maxM = 2001;
const ll maxT = 5001;
const ll INF = 10000000000;
map<ll,vector<int>> adj;
map<ll,vector<int>> adj1;
ll m[maxN];
int main(){
  freopen("time.in", "r", stdin);
  freopen("time.out", "w", stdout);
  IO
  ll N,M,C;
  cin >> N >> M >> C;
  for(ll i = 0; i < N; i++){
    cin >> m[i];
  }
  for(ll i = 0; i < M; i++){
    ll u,v;
    cin >> u >> v;
    adj[u - 1].pb(v - 1);
    adj1[v - 1].pb(u - 1);
  }
  //ll DP[maxT][N];
  vector<ll> cur(N);
  vector<ll> prev(N);
  ll myMax = 0;
  prev[0] = 0;
  for(ll i = 1; i < N; i++){
    prev[i] = -INF;
  }
  for(ll i = 2; i < maxT; i++){
    for(ll j = 0; j < N; j++){
      cur[j] = -INF;
      for(ll k: adj1[j]){
        cur[j] = max(prev[k] + m[j],cur[j]);
      }
      //myMax = max(cur[j] - C * (i) * (i),myMax);
    }
    myMax = max(cur[0] - C * (i - 1) * (i - 1), myMax);
    prev = cur;
  }
  cout << myMax << endl;
}
