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
int adj[1001][1001];
bool operator<(const bessie a1, const bessie a2) {
  if (a1.x != a2.x) {
    return a1.x < a2.x;
  }
  vector<int> v1 = {a1.x, a1.y, a1.oranges, a1.dirx, a1.diry};
  vector<int> v2 = {a2.x, a2.y, a2.oranges, a2.dirx, a2.diry};
  return v1 < v2;
}
int n, m;
bool inBounds(int x, int y) { return x >= 0 && y >= 0 && x < n && y < m; }
class Problem3BessiesDream {
public:
  vector<pair<int, int>> d;
  void solve(std::istream &in, std::ostream &out) {
    d.push_back({0, 1});
    d.push_back({1, 0});
    d.push_back({-1, 0});
    d.push_back({0, -1});
    in >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        in >> adj[i][j];
      }
    }
    queue<pair<int, bessie>> q;
    if (adj[0][0] == 2) {
      // if it's an orange tile
      for (pair<int, int> p : d) {
        int i = p.first;
        int j = p.second;
        if (abs(i) == abs(j)) {
          continue;
        }
        q.push({0, {0, 0, 1, i, j}});
      }
    } else {
      for(pair<int,int> p: d){
        int i = p.first;
        int j = p.second;
        q.push({0, {0, 0, 0, i, j}});
      }
    }
    int vis[n][m][2][3][3];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < 2; k++) {
          for (int l = 0; l < 3; l++) {
            for (int o = 0; o < 3; o++) {
              vis[i][j][k][l][o] = false;
            }
          }
        }
      }
    }
    while (!q.empty()) {
      bessie cur = q.front().second;
      // out << cur.x << " " << cur.y << endl;
      int dist = q.front().first;
      q.pop();
      if (cur.x == n - 1 && cur.y == m - 1) {
        out << dist << endl;
        return;
      }
      if (cur.x < 0 || cur.y < 0 || cur.x >= n || cur.y >= m) {
        continue;
      }
      if (vis[cur.x][cur.y][cur.oranges][cur.dirx + 1][cur.diry + 1]) {
        continue;
      }
      vis[cur.x][cur.y][cur.oranges][cur.dirx + 1][cur.diry + 1] = true;
      if (adj[cur.x][cur.y] == 0) {
        continue;
      } else if (adj[cur.x][cur.y] == 1) {
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          q.push({dist + 1, {cur.x + i, cur.y + j, cur.oranges, i, j}});
        }
      } else if (adj[cur.x][cur.y] == 2) {
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          q.push({dist + 1, {cur.x + i, cur.y + j, 1, i, j}});
        }
      } else if (adj[cur.x][cur.y] == 3) {
        if (cur.oranges == 0) {
          continue;
        }
        for (pair<int, int> p : d) {
          int i = p.first;
          int j = p.second;
          q.push({dist + 1, {cur.x + i, cur.y + j, 1, i, j}});
        }
      } else if (adj[cur.x][cur.y] == 4) {
        if (cur.x + cur.dirx < 0 || cur.x + cur.dirx >= n) {
          continue;
        }
        if (cur.y + cur.diry < 0 || cur.y + cur.diry >= m) {
          continue;
        }
        if (!inBounds(cur.x + cur.dirx, cur.y + cur.diry) ||
            adj[cur.x + cur.dirx][cur.y + cur.diry] % 3 == 0) {
          for (pair<int, int> p : d) {
            int i = p.first;
            int j = p.second;
            q.push({dist + 1, {cur.x + i, cur.y + j, 0, i, j}});
          }
        } else {
          q.push({dist + 1,
                  {cur.x + cur.dirx, cur.y + cur.diry, 0, cur.dirx, cur.diry}});
        }
      }
    }
    out << -1 << '\n';
  }
};
