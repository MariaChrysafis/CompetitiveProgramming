#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;
struct square{
  int length, width;
};
struct Edge{
  int weight;
  int u;
  int v;
};
vector<Edge>edges;
struct less_than_key
{
  inline bool operator() (const Edge& struct1, const Edge& struct2)
  {
    return (struct1.weight < struct2.weight);
  }
};
struct Graph{
  vector<int> parent;
  vector<int>_rank;
  int v;
  int e;
  int find_set(int x){
    if(x == parent[x]) return x;
    return parent[x] = find_set(parent[x]);
  }
  bool union_set(int x, int y){
    int i = find_set(x);
    int j = find_set(y);
    if(i != j){
      if(_rank[i] > _rank[j]){
        parent[j] = i;
        _rank[i] += _rank[j];
      }else{
        parent[i] = j;
        _rank[j] += _rank[i];
      }
      return true;
    }
    return false;
  }
  int kruskal(){
    long long mst = 0;
    int k = 0;
    int w, x, y;

    sort(edges.begin(), edges.end(),less_than_key());

    for(int i = 0; i < e && k < v - 1; i++){
      w = edges[i].weight;
      x = edges[i].u;
      y = edges[i].v;

      if(union_set(x, y)){
        mst += w;
        k++;
      }
    }
    return mst;
  }

  int do_stuff(){
    for(int i = 0; i < v; i++){
      _rank[i] = 0;
      parent[i] = i;
    }
    return kruskal();
  }
};
class Problem3FencedIn {
public:
  void solve(std::istream &in, std::ostream &out) {
    int A,B,n,m;
    in >> A >> B >> n >> m;
    vector<int> vertical, horizontal;
    for(int i = 0; i < n; i++){
      int a;
      in >> a;
      vertical.push_back(a);
    }
    vertical.push_back(A);
    vertical.push_back(0);
    sort(vertical.begin(),vertical.end());
    for(int i = 0; i < m; i++){
      int a;
      in >> a;
      horizontal.push_back(a);
    }
    horizontal.push_back(0);
    horizontal.push_back(B);
    sort(horizontal.begin(),horizontal.end());
    n++;
    m++;
    square arr[m][n];
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        int s1 = horizontal[i + 1] - horizontal[i];
        int s2 = vertical[j + 1] - vertical[j];
        arr[i][j] = {s1,s2};
      }
    }
    int cntr = 0;
    int match[m][n];
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        match[i][j] = cntr;
        cntr++;
      }
    }
    vector<pair<int,int>> dir;
    dir.push_back({-1,0});
    dir.push_back({1,0});
    dir.push_back({0,-1});
    dir.push_back({0,1});
    vector<pair<int,int>> result;
    edges.resize((n * (m + 1) + m * (n + 1)) * 2);
    int cc = 0;
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        for(pair<int,int> p: dir){
          int new_i = p.first + i;
          int new_j = p.second + j;
          if(new_i >= m || new_j >= n || new_i < 0 || new_j < 0){
            continue;
          }
          int weight;
          if(p.second == 0){
            weight = arr[i][j].width;
          }else{
            weight = arr[i][j].length;
          }
          edges[cc] = {weight,match[i][j],match[new_i][new_j]};
          cc++;
        }
      }
    }
    vector<int> vec(n * m);
    Graph g;
    g.parent = vec;
    g._rank = vec;
    g.e = edges.size();
    g.v = n * m;
    int x = g.do_stuff();
    out << x << endl;
  }
};
