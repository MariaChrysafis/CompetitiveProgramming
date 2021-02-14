#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
struct bessie {
  int x;
  int y;
  bool oranges;
  int dirx;
  int diry;
};
int adj[1000][1000];
bool operator<(const bessie a1, const bessie a2) {
  vector<int> v1 = {a1.x, a1.y, a1.oranges, a1.dirx, a1.diry};
  vector<int> v2 = {a2.x, a2.y, a2.oranges, a2.dirx, a2.diry};
  return v1 < v2;
}
bool inBounds(int x, int y, int n, int m){
  if(x >= n || y >= m || x < 0 || y < 0){
    return false;
  }
  return true;
}
class Problem3BessiesDream {
public:
  vector<pair<int, int>> d;
  void solve(std::istream &in, std::ostream &out) {
    d.push_back({0, 1});
    d.push_back({1, 0});
    d.push_back({-1, 0});
    d.push_back({0, -1});
    int n, m;
    in >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        in >> adj[i][j];
      }
    }
    queue<pair<int, bessie>> q;
    if (adj[0][0] == 2) {
      // if it's an orange tile
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          if (abs(i) == abs(j)) {
            continue;
          }
          q.push({0, {0, 0, 1, i, j}});
        }
      }
    } else {
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          if (abs(i) == abs(j)) {
            continue;
          }
          q.push({0, {0, 0, 0, i, j}});
        }
      }
    }
    map<bessie, int> vis;
    while (!q.empty()) {
      bessie cur = q.front().second;
      int dist = q.front().first;
      q.pop();
      if (cur.x == n - 1 && cur.y == m - 1) {
        out << dist << endl;
        return;
      }
      if(vis[cur]){
        continue;
      }
      if (adj[cur.x][cur.y] == 0) {
        continue;
      }else if (adj[cur.x][cur.y] == 1) {
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          if(inBounds(cur.x + i,cur.y + j,n,m)){
            bessie ans = {cur.x + i, cur.y + j, cur.oranges, i, j};
            q.push({dist + 1, ans});
            vis[cur] = true;
          }
        }
      }else if (adj[cur.x][cur.y] == 2) {
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          if(inBounds(cur.x + i, cur.y + j,n,m)) {
            bessie ans = {cur.x + i, cur.y + j, 1, i, j};
            q.push({dist + 1, ans});
            vis[cur] = true;
          }
        }
      }else if (adj[cur.x][cur.y] == 3) {
        if (cur.oranges == 0) {
          continue;
        }
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          bessie ans = {cur.x + i, cur.y + j, 1, i, j};
          if(inBounds(cur.x + i, cur.y + j, n, m) && !vis[ans]) {
            q.push({dist + 1, ans});
            vis[cur] = true;
          }
        }
      }else if (adj[cur.x][cur.y] == 4) {
        if(cur.x + cur.dirx < 0 || cur.x + cur.dirx >= n){
          continue;
        }
        if(cur.y + cur.diry < 0 || cur.y + cur.diry >= m){
          continue;
        }
        //int nxt = adj[cur.x + cur.dirx][cur.y + cur.diry];
        int newX = cur.x + cur.dirx;
        int newY = cur.y + cur.diry;
        if(!inBounds(newX,newY,n,m)||adj[newX][newY] == 3||adj[newX][newY] == 0){
          for (pair<int, int> p : d) {
            int i = p.first;
            int j = p.second;
            bessie ans = {cur.x + i, cur.y + j, 0, i, j};
            if(inBounds(cur.x + i, cur.y + j, n, m) && !vis[ans]) {
              vis[cur] = true;
              q.push({dist + 1, ans});
            }
          }
        }else {
          bessie ans = {cur.x + cur.dirx, cur.y + cur.diry, 0, cur.dirx, cur.diry};
          if(!inBounds(cur.x + cur.dirx, cur.y + cur.diry, n, m) || vis[ans]){
            continue;
          }
          vis[cur] = true;
          q.push({dist + 1,ans});
        }
      }
    }
    out << -1 << endl;
  }
};
