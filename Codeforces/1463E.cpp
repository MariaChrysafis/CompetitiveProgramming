#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>
#include <unordered_map>
using namespace std;
class Solution {
  const int n
  cont int k;
  int* arr;
  map<pair<int, int>, int> color;
  vector<int> Color;
  unordered_map<int,vector<int>> adj; /* colored version */
  unordered_map<int,vector<int>> adj_invert; /* inverted colored graph */
  vector<vector<int>> adj1; /* uncolored version */
  vector<int> indeg;
  vector<int> indeg1;
  map<int, bool> hv;
  vector<vector<int>> comp; /* merge into a node */
  vector<vector<int>> components; /* post-transformation */
  vector<int> head;
 
  void dfs(int x, int c, int orig) {
    hv[x] = true;
    head[x] = orig;
    comp[orig].push_back(x);
    for (int i: adj[x]) {
      if (hv[i]) {
        continue;
      }
      if (color[{x, i}] == c) {
        dfs(i, c, orig);
      }
    }
    for (int i: adj_invert[x]) {
      if (hv[i]) {
        continue;
      }
      if (color[{i, x}] == c) {
        dfs(i, c, orig);
      }
    }
  }
  void dfs1(int x, int num) {
    hv[x] = true;
    components[num].push_back(x);
    for (int i: adj[x]) {
      if (hv[i]) {
        continue;
      }
      dfs1(i, num);
    }
    for (int i: adj_invert[x]) {
      if (hv[i]) {
        continue;
      }
      dfs1(i, num);
    }
  }
 
  vector<int> topo_sort(vector<int> v) {
    vector<int> cur;
    queue<int> q;
    for (int i: v) {
      if (indeg[i] == 0) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      for (int i: adj[q.front()]) {
        indeg[i]--;
        if (indeg[i] == 0) {
          q.push(i);
        }
      }
      cur.push_back(q.front());
      q.pop();
    }
    return cur;
  }
 
  vector<int> topo_sort1(vector<int> v) {
    vector<int> cur;
    queue<int> q;
    for (int i: v) {
      if (indeg1[i] == 0) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      for (int i: adj1[q.front()]) {
        indeg1[i]--;
        if (indeg1[i] == 0) {
          q.push(i);
        }
      }
      cur.push_back(q.front());
      q.pop();
    }
    return cur;
  }
 
public:
  Solution(int N, int K)
      : n(N), k(K), arr(new int[N]) {
  }
 
  int run() {
 
    head.resize(n);
    indeg.resize(n);
    indeg1.resize(n);
    comp.resize(n);
    components.resize(n);
    adj1.resize(n);
    Color.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
      head[i] = i;
    }
    vector<pair<int, int>> inp;
    for (int i = 0; i < k; i++) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      inp.push_back({a, b});
      color[{a, b}] = 1;
      adj[a].push_back(b);
      adj_invert[b].push_back(a);
      Color[a] = Color[b] = 1;
    }
    for (int i = 0; i < n; i++) {
      if (!hv[i] && Color[i] == 1) {
        dfs(i, Color[i], i);
      }
    }
    adj.clear();
    adj_invert.clear();
    for (int i = 0; i < n; i++) {
      if (arr[i] == 0) {
        continue;
      }
      int u = head[arr[i] - 1];
      int v = head[i];
      if (u == v) {
        continue;
      }
      adj[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
      for (int j: adj[i]) {
        indeg[j]++;
      }
    }
    for (pair<int, vector<int>> p: adj) {
      for (int i: adj[p.first]) {
        adj_invert[i].push_back(p.first);
      }
    }
    hv.clear();
    for (int i = 0; i < k; i++) {
      int a = inp[i].first;
      int b = inp[i].second;
      adj1[a].push_back(b);
      indeg1[b]++;
    }
    int num = 0;
    for (int i = 0; i < n; i++) {
      if (!hv[i] && head[i] == i) {
        components[num].push_back(1);
        components[num].pop_back();
        dfs1(i, num);
        num++;
      }
    }
    vector<int> ans;
    for (int i = 0; i < components.size(); i++) {
      vector<int> v1 = topo_sort(components[i]);
      for (int j: v1) {
        if (comp[j].size() != 0) {
          vector<int> v2 = topo_sort1(comp[j]);
          for (int k: v2) {
            ans.push_back(k);
          }
        }
        else {
          ans.push_back(j);
        }
      }
    }
    if (ans.size() != n) {
      cout << 0 << endl;
      return 0;
    }
    map<int, int> ind;
    for (int i = 0; i < n; i++) {
      ind[ans[i]] = i;
    }
    for (int i = 0; i < k; i++) {
      if (ind[inp[i].second] - ind[inp[i].first] != 1) {
        cout << 0 << endl;
        return 0;
      }
    }
    for (int i = 0; i < n; i++) {
      if (arr[i] == -1) {
        continue;
      }
      int a = arr[i] - 1;
      int b = i;
      if (ind[a] > ind[b]) {
        cout << 0 << endl;
        return 0;
      }
    }
    for (int i: ans) {
      cout << i + 1 << " ";
    }
    return 0;
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  int k;
  cin >> n >> k;
  Solution *self = new Solution(n,k);
  self->run();
}
