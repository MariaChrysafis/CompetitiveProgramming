/*
   REMINDERS TO SELF:
   - think before implementing
   - CF likes to troll with long long vs int stuff
   - a crazy person repeats the same thing expecting the same result
   - don't create unneeded edge cases
   - nutella
*/
// Created by Maria Chrysafis
//Time: $%Y%$-$%M%$-$%D%$ $%h%$:$%m%$:$%s%$
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
#define vi vector<int>
#define vpii vector<pair<int,int>>
#define REP(i,a) for(int i = 0; i < a; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define input freopen("timeline.in", "r", stdin); freopen("timeline.out", "w", stdout);
using namespace std;
map<int,vpii> adj;
int main(){
  IO
  input
  int N,M,C;
  cin >> N >> M >> C;
  int S[N];
  REP(i,N) cin >> S[i];
  int in_degree[N];
  REP(i,N) in_degree[i] = 0;
  REP(i,C){
    int x,y,z;
    cin >> x >> y >> z;
    x--;
    y--;
    in_degree[y]++;
    adj[x].pb(mp(y,z));
  }
  queue<int> q;
  REP(i,N){
    if(in_degree[i] == 0){
      q.push(i);
    }
  }
  while(!q.empty()){
    int x = q.front();
    q.pop();
    trav(i,adj[x]){
      S[i.first] = max(S[i.first],S[x] + i.second);
      in_degree[i.first]--;
      if(in_degree[i.first] == 0){
        q.push(i.first);
      }
    }
  }
  REP(i,N){
    cout << S[i] << endl;
  }
  return 0;
}

