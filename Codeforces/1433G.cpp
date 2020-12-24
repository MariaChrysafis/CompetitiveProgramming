#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
using namespace std;
int n,m,k;
struct Pair{
  int neighbor;
  int weight;
};
struct Edge{
  int u,v,weight;
};
bool operator <(Pair a, Pair b){
  return a.weight > b.weight;
}
unordered_map<int,vector<Pair>> adj;
vector<vector<int>> Dist;
void dijk(int MAX, int INFTY, int src){
  bool mark[MAX];
  vector<int> dist;
  dist.resize(MAX);
  for(int i = 0; i < MAX; i++){
    mark[i] = 0;
    dist[i] = INFTY;
  }
  dist[src] = 0;
  priority_queue<Pair> pq;
  pq.push({src,0});
  while(!pq.empty()){
    int x = pq.top().neighbor;
    pq.pop();
    if(mark[x]){
      continue;
    }
    mark[x] = 1;
    for(int j = 0; j < adj[x].size(); j++){
      int a = adj[x][j].neighbor;
      int b = adj[x][j].weight;
      if(dist[a] > dist[x] + b){
        dist[a] = dist[x] + b;
        Pair c = {a,dist[x] + b};
        pq.push(c);
      }
    }
  }
  Dist.push_back(dist);
}
int main(){
  cin >> n >> m >> k;
  vector<Edge> edges;
  for(int i = 0; i < m; i++){
    int a,b,c;
    cin >> a >> b >> c;
    a--;
    b--;
    adj[a].push_back({b,c});
    adj[b].push_back({a,c});
    edges.push_back({a,b,c});
  }
  for(int i = 0; i < n; i++){
    dijk(1001,1000000000,i);
  }
  vector<pair<int,int>> input;
  for(int i = 0; i < k; i++){
    int a,b;
    cin >> a >> b;
    a--;
    b--;
    input.push_back({a,b});
  }
  int ans = 0;
  for(int i = 0; i < m; i++){
    //change the ith edge
    int u = edges[i].u;
    int v = edges[i].v;
    int w = edges[i].weight;
    int sum = 0;
    for(pair<int,int> p: input){
      int myMin = min(Dist[p.first][p.second],Dist[p.first][u] + Dist[v][p.second]);
      myMin = min(myMin,Dist[p.first][v] + Dist[u][p.second]);
      sum += myMin;
    }
    if(i == 0){
      ans = sum;
    }else{
      ans = min(ans,sum);
    }
  }
  cout << ans << endl;
}
