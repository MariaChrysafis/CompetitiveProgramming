#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
class Graph {
 public:
  Graph(int n) {
    adj.resize(n), start.assign(n, -1), hasVisited.assign(n, false);
    low.assign(n, -1);
  }
  void add_edge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
  void dfs(int curNode, int prevNode) {
    hasVisited[curNode] = true;
    start[curNode] = low[curNode] = ++cntr;
    int children = 0;
    bool fine = false;
    for (int i : adj[curNode]) {
      if (i != prevNode) {
        if (hasVisited[i]) {
          low[curNode] = min(low[curNode], start[i]);
        } else {
          dfs(i, curNode);
          low[curNode] = min(low[curNode], low[i]);
          fine = fine || (low[i] >= start[curNode] && prevNode != -1);
          children++;
        }
      }
    }
    if ((children > 1 && prevNode == -1) || fine) {
      articulation.push_back(curNode);
    }
  }
  void find_articulation() {
    for (int i = 0; i < (int)adj.size(); i++) {
      if (!hasVisited[i]) {
        dfs(i, -1);
      }
    }
  }
  vector<vector<int> > adj;
  vector<bool> hasVisited;
  vector<int> start, low;
  vector<int> articulation;
  int cntr = 0;
};
 
int main() {
  int n, m;
  cin >> n >> m;
  Graph gr(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    gr.add_edge(u - 1, v - 1);
  }
  gr.find_articulation();
  cout << gr.articulation.size() << '\n';
  for (int i = 0; i < gr.articulation.size(); i++) {
    cout << gr.articulation[i] + 1 << ' ';
  }
}
