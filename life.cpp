#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;
class Problem2MoorioKart {
public:
  int N, M, X, Y;
  vector<vector<pair<int,int>>> adj;
  vector<int> connectComponent;
  vector<vector<int>> forest;
  map<int,vector<vector<int>>> myMap;
  void dfs(int cc, int node1, int prevNode){
    connectComponent[node1] = cc;
    for(pair<int,int> p: adj[node1]){
      if(p.first == prevNode){
        continue;
      }
      dfs(cc,p.first,node1);
    }
  }
  vector<int> bfs(vector<int> v, int strt){
    //v gives the nodes that we are considering
    //vector<int> ans;
    map<int,bool> hasVisited;
    queue<pair<int,int>> q;
    map<int,int> ans;
    q.push({strt,0});
    while(!q.empty()){
      int no = q.front().first;
      int we = q.front().second;
      hasVisited[no] = true;
      ans[no] = (we);
      q.pop();
      for(pair<int,int> p: adj[no]){
        if(hasVisited[p.first]) continue;
        q.push({p.first, p.second + we});
      }
    }
    vector<int> vec;
    for(int i: v){
      vec.push_back(ans[i]);
    }
    return vec;
  }
  void solve(std::istream &in, std::ostream &out) {
    in >> N >> M >> X >> Y;
    adj.resize(N);
    for(int i = 0; i < M; i++){
      int a,b,c;
      in >> a >> b >> c;
      a--;
      b--;
      adj[a].push_back({b,c});
      adj[b].push_back({a,c});
    }
    int cc = 0;
    connectComponent.resize(N);
    for(int i = 0; i < N; i++){
      connectComponent[i] = -1;
    }
    for(int i = 0; i < N; i++){
      if(connectComponent[i] == -1){
        dfs(cc,i,-1);
        cc++;
      }
    }
    forest.resize(cc);
    for(int i = 0; i < N; i++){
      forest[connectComponent[i]].push_back(i);
    }
    //vector<int> ans = bfs({3,4},4);
    vector<vector<int>> path;
    vector<int> path_sum;
    path.resize(cc);
    path_sum.resize(cc);
    for(int i = 0; i < cc; i++){
      vector<vector<int>> grid;
      for(int j: forest[i]){
        vector<int> ans = bfs(forest[i],j);
        grid.push_back(ans);
      }
      //flatten out the grid
      for(int j = 0; j < grid.size(); j++){
        for(int k = 0; k < j; k++){
          path[i].push_back(grid[j][k]);
        }
      }
    }
    for(int i = 0; i < cc; i++){
      path_sum[i] = 0;
      for(int j: path[i]){
        path_sum[i] += j;
      }
    }
    map<int,int> oc;
    int ans = 0;
    int prod = 1;
    for(int i = 0; i < cc; i++){
      int cntr = 1;
      prod = 1;
      for(int j = 0; j < cc; j++){
        prod *= path[j].size();
        if(i == j) continue;
        cntr *= path[j].size();
      }
      ans += cntr * path_sum[i];
    }
    ans += X * prod * cc;
    out << ans << endl;
  }
};
