#include <bits/stdc++.h>

using namespace std;

struct biconnected_components{
  int cnt;
  vector<int> bcc;
  biconnected_components(vector<vector<pair<int, int> > > &E){
    int N = E.size();
    vector<int> next(N, -1);
    vector<int> d(N, -1);
    vector<int> imos(N, 0);
    for (int i = 0; i < N; i++){
      if (d[i] == -1){
        d[i] = 0;
        dfs1(E, next, d, imos, i);
      }
    }
    int M = 0;
    for (int i = 0; i < N; i++){
      M += E[i].size();
    }
    M /= 2;
    bcc = vector<int>(M, -1);
    cnt = 0;
    for (int i = 0; i < N; i++){
      if (d[i] == 0){
        dfs2(E, d, imos, cnt, i);
      }
    }
  }
  void dfs1(vector<vector<pair<int, int> > > &E, vector<int> &next, vector<int> &d, vector<int> &imos, int v){
    for (auto& P : E[v]){
      int w = P.second;
      if (d[w] == -1){
        d[w] = d[v] + 1;
        next[v] = w;
        dfs1(E, next, d, imos, w);
        imos[v] += imos[w];
      } else if (d[w] < d[v] - 1){
        imos[v]++;
        imos[next[w]]--;
      }
    }
  }
  void dfs2(vector<vector<pair<int, int> > > &E, vector<int> &d, vector<int> &imos, int b, int v){
    for (auto P : E[v]){
      int x = P.first;
      int w = P.second;
      if (d[w] < d[v]){
        bcc[x] = b;
      } else if (d[w] == d[v] + 1 && bcc[x] == -1){
        if (imos[w] > 0){
          bcc[x] = b;
        } else {
          bcc[x] = cnt;
          cnt++;
        }
        dfs2(E, d, imos, bcc[x], w);
      }
    }
  }
  int operator [](int k){
    return bcc[k];
  }
  int count(){
    return cnt;
  }
};

struct State {
    pair<int,int> me;
    pair<int,int> box;
    bool operator < (const State& s1) const {
        if (s1.me != me) return (s1.me < me);
        return (s1.box < box);
    }
    void print() {
        cout << me.first << " " << me.second << " " << box.first << " " << box.second << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("pushabox.in", "r", stdin);
    freopen("pushabox.out", "w", stdout);
    int n, m, q;
    cin >> n >> m >> q;
    string grid[n];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    vector<vector< pair<int,int> > > edges(n * m);
    int c = 0;
    int myMap[n][m][3][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx + i < 0 || dx + i == n) continue;
                for (int dy = -1; dy <= 1; dy++) {
                    if (dy + j < 0 || dy + j == m) continue;
                    if (make_pair(i, j) < make_pair(i + dx, j + dy)) continue;
                    if (abs(dx) + abs(dy) == 1 && grid[i][j] != '#' && grid[i + dx][j + dy] != '#') {
                        edges[m * i + j].push_back(make_pair(c, m * (i + dx) + j + dy));
                        edges[m * (i + dx) + j + dy].push_back(make_pair(c,m * i + j ));
                        myMap[i][j][dx + 1][dy + 1] = c;
                        myMap[i + dx][j + dy][-dx + 1][-dy + 1] = c;
                        c++;
                    }
                }
            }
        }
    }
    biconnected_components g(edges);
    State cur;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') cur.me = make_pair(i, j);
            else if (grid[i][j] == 'B') cur.box = make_pair(i, j);
        }
    }
    queue<pair<int,int> > dum;
    dum.push(cur.me);
    bool okay[n][m];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) okay[i][j] = false;
    queue<State> myQueue;
    while (!dum.empty()) {
        pair<int,int> p = dum.front();
        dum.pop();
        if (okay[p.first][p.second]) continue;
        okay[p.first][p.second] = true;
        if (abs(p.first - cur.box.first) + abs(p.second - cur.box.second) == 1) {
            State myState; myState.me = p, myState.box = cur.box;
            myQueue.push(myState);
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && p.first + dx >= 0 && p.first + dx < n && p.second + dy >= 0 && p.second + dy < m && grid[p.first + dx][p.second + dy] == '.') {
                    if (!okay[p.first + dx][p.second + dy]) dum.push(make_pair(p.first + dx, p.second + dy));
                }
            }
        }
    }
    bool pos[n][m];
    bool vis[n][m][3][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pos[i][j] = false;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    vis[i][j][x][y] = false;
                }
            }
        }
    }
    while (!myQueue.empty()) {
        State myState = myQueue.front();
        myQueue.pop();
        if (vis[myState.me.first][myState.me.second][myState.box.first - myState.me.first + 1][myState.box.second - myState.me.second + 1]) continue;
        vis[myState.me.first][myState.me.second][myState.box.first - myState.me.first + 1][myState.box.second - myState.me.second + 1] = true;
        pos[myState.box.first][myState.box.second] = true;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy ++) {
                if (myState.box.first + dx == myState.me.first && myState.box.second + dy == myState.me.second) {
                    continue;
                }
                if (abs(dx) + abs(dy) != 1) continue;
                pair<int,int> new_me = make_pair(myState.box.first + dx, myState.box.second + dy);
                if (new_me.first < 0 || new_me.second < 0 || new_me.first == n || new_me.second == m || grid[new_me.first][new_me.second] == '#') continue;
                int a = myMap[myState.me.first][myState.me.second][myState.box.first - myState.me.first + 1][myState.box.second - myState.me.second + 1];
                int b = myMap[new_me.first][new_me.second][myState.box.first - new_me.first + 1][myState.box.second - new_me.second + 1];
                if (g[a] != g[b]) continue;
                State nxt;
                nxt.box = myState.box;
                nxt.me = new_me;
                if (!vis[nxt.me.first][nxt.me.second][nxt.box.first - nxt.me.first + 1][nxt.box.second - nxt.me.second + 1])
                myQueue.push(nxt);
            }
        }
        pair<int,int> nxt = make_pair(2 * myState.box.first - myState.me.first, 2 * myState.box.second - myState.me.second);
        if (nxt.first < 0 || nxt.first == n) continue;
        if (nxt.second < 0 || nxt.second == m) continue;
        if (grid[nxt.first][nxt.second] == '#') continue;
        myState.me = myState.box;
        myState.box = nxt;
        if (vis[myState.me.first][myState.me.second][myState.box.first - myState.me.first + 1][myState.box.second - myState.me.second + 1]) continue;
        myQueue.push(myState);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (pos[u][v]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

}
