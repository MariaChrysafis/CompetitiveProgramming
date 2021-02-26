/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>

#include <map>
#include <cmath>
using namespace std;
class Problem2MilkVisits {
public:
  vector<vector<int>> adj;
  vector<int> milk;
  struct Tree{
    int cntr;
    vector<vector<int>> up;
    vector<int> f, s;
    vector<int> sub;
    int n, l;
    vector<vector<int>> adj;
    void dfsForLCA(int u, int prev){
      f[u] = cntr;
      cntr++;
      up[u][0] = prev;
      for(int i = 1; i <= l; i++){
        up[u][i] = up[up[u][i - 1]][i - 1];
      }
      for(int v: adj[u]){
        if(v != prev){
          dfsForLCA(v, u);
        }
      }
      s[u] = cntr;
      cntr++;
    }
    bool isAncestor(int u, int v){
      return f[u] <= f[v] && s[u] >= s[v];
    }
    int lca(int u, int v){
      if(isAncestor(u,v)){
        return u;
      }
      if(isAncestor(v,u)){
        return v;
      }
      for(int i = l; i >= 0; i--){
        if(!isAncestor(up[u][i],v)){
          u = up[u][i];
        }
      }
      return up[u][0];
    }
  };
  struct query{
    int a;
    int b;
    int c;
    int ind;
  };
  Tree t;
  vector<vector<int>> vs;
  map<int,vector<int>> myMap;
  vector<bool> ans;
  vector<query> vq;
  void dfs(int u, int prev){
    vs[milk[u]].push_back(u);
    for(int x: myMap[u]){
      query q = vq[x];
      if(vs[q.c].empty()){
        continue;
      }
      int lst = vs[q.c].back();
      int LCA = t.lca(q.a,q.b);
      if(t.sub[LCA] >= t.sub[lst]){
        ans[q.ind] = true;
      }
    }
    for(int v: adj[u]){
      if(v != prev){
        dfs(v,u);
      }
    }
    vs[milk[u]].pop_back();
  }
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    int q;
    in >> q;
    milk.resize(n), adj.resize(n), ans.resize(q), vs.resize(n + 1);
    for(int i = 0; i < n; i++){
      in >> milk[i];
    }
    for(int i = 0; i < n - 1; i++){
      int u, v;
      in >> u >> v;
      u--;
      v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    vector<int> dum(n);
    vector<vector<int>> up;
    up.resize(n);
    for(int i = 0; i < n; i++){
      up[i].resize(ceil(log2(1.0 * n)) + 1);
    }
    t.n = n, t.l = ceil(log2(1.0 * n));
    t.f = dum, t.s = dum, t.sub = dum, t.up = up;
    t.cntr = 0;
    t.adj = adj;
    t.dfsForLCA(0, 0);
    for(int i = 0; i < n; i++){
      t.sub[i] = t.s[i] - t.f[i];
    }
    for(int i = 0; i < q; i++){
      int a, b, c;
      in >> a >> b >> c;
      a--;
      b--;
      vq.push_back({a,b,c,i});
      myMap[a].push_back(i);
      myMap[b].push_back(i);
    }
    dfs(0,-1);
    for(int j: ans){
      out << j;
    }
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
	Problem2MilkVisits solver;
	std::ifstream in("milkvisits.in");
	std::ofstream out("milkvisits.out");
	solver.solve(in, out);
	return 0;
}
