#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#define endl '\n'
const long long INFTY = 1000000000;
using namespace std;
struct edge{
  long long u, weight;
};
//vector<int> DIST;
struct compareEdge{
  bool operator()(edge const& p1, edge const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.weight > p2.weight;
    }
};
long long max(long long a, long long b){
  if(a > b){
    return a;
  }
  return b;
}
struct graph{
  vector<vector<edge>> adj;
  vector<long long> parent;
  vector<long long> cow;
  vector<long long> c;
  int N, M, T;
  void init(){
    adj.resize(N);
    parent.resize(N);
    cow.resize(N);
    for(int i = 0; i < N; i++){
      cow[i] = 0, parent[i] = INFTY;
    }
  }
  vector<long long> dijk() {
    int n = N;
    bool mark[N + 1];
    priority_queue<edge, vector<edge>, compareEdge> pq;
    for(int i = 0; i < n; i++){
      mark[i] = false;
    }
    vector<long long> dist(N + 1);
    for(int i = 0; i < N; i++){
      dist[i] = INFTY;
    }
    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty()){
      int x = pq.top().u;
      pq.pop();
      if(mark[x]){
        continue;
      }
      mark[x] = true;
      for(int j = 0; j < adj[x].size(); j++){
        int a = adj[x][j].u;
        int b = adj[x][j].weight;
        //if(dist[x] = INF) continue;
        if(dist[a] > dist[x] + b || (dist[a] == dist[x] + b && x < parent[a])){
          dist[a] = dist[x] + b;
          edge c = {a,dist[x] + b};
          pq.push(c);
          parent[a] = x;
        }
      }
    }
    return dist;
  }
  void path(int strt, int cur){
    cow[cur] += c[strt];
    if(cur == 0){
      return;
    }else{
      //curPath.push_back(parent[curPath.back()]);
      path(strt, parent[cur]);
    }
  }
};
int main(){
  freopen("shortcut.in", "r", stdin);
  freopen("shortcut.out", "w", stdout);
  //ifstream in("shortcut.in");
	//ofstream out("shortcut.out");
  int N, M, T;
  cin >> N >> M >> T;
  graph g;
  g.N = N, g.M = M, g.T = T, g.init();
  vector<long long> c;
  for(int i = 0; i < N; i++){
    int a; cin >> a;
    c.push_back(a);
  }
  g.c = c;
  for(int i = 0; i < M; i++){
    int a, b, t;
    cin >> a >> b >> t, a--, b--;
    g.adj[a].push_back({b,t});
    g.adj[b].push_back({a,t});
  }
  vector<long long> dist = g.dijk();
  long long myMax = 0;
  for(int i = 0; i < N; i++){
    g.path(i, i);
  }
  for(int i = 1; i < N; i++){
    if(dist[i] == INFTY){
      //cout << "YES" << endl;
        //continue;
    }
    myMax = max(g.cow[i] * (dist[i] - T), myMax);
  }
  cout << myMax << endl;
}
