#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

const int INF = 1e9;

vector<vector<char>> grid;
vector<vector<int>> comp;
vector<vector<pair<int,int>>> cc;
vector<vector<int>> dist;

bool inRange (int x, int y) {
    return (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size());
}

int CONNECTED_COMPONENT_COUNT = 0;
void dfs_for_connected_component (int x, int y) {
    if (comp[x][y] != -1) {
        return;
    }
    comp[x][y] = CONNECTED_COMPONENT_COUNT;
    cc.back().emplace_back(x, y);
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (inRange(x + dx, y + dy) && grid[x + dx][y + dy] == 'X' && abs(dx) != abs(dy)) {
                dfs_for_connected_component(x + dx, y + dy);
            }
        }
    }
}

void update_distances (int src) {
    vector<vector<int>> di;
    di.resize(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        di[i].assign(grid[0].size(), INF);
    }
    deque<pair<pair<int,int>,int>> q;
    assert(!cc[src].empty());
    q.push_back({cc[src].back(), 0});
    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int d = q.front().second;
        q.pop_front();
        if (di[x][y] <= d) {
            continue;
        }
        di[x][y] = d;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (inRange(x + dx, y + dy) && abs(dx) != abs(dy)) {
                    if (grid[x + dx][y + dy] == 'S') {
                        q.push_back({{x + dx, y + dy}, d + 1});
                    } else if (grid[x + dx][y + dy] == 'X'){
                        q.push_front({{x + dx, y + dy}, d});
                    }
                }
            }
        }
    }
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != 'X' || di[i][j] == INF) {
                continue;
            }
            assert(comp[i][j] >= 0);
            assert(comp[i][j] < cc.size());
            dist[src][comp[i][j]] = min(dist[src][comp[i][j]], di[i][j]);
        }
    }
}

int main() {
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
    int R, C;
    cin >> R >> C;
    grid.resize(R);
    for (int i = 0; i < R; i++) {
        grid[i].resize(C);
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
        }
    }
    comp.resize(R);
    for (int i = 0; i < R; i++) {
        comp[i].assign(C, -1);
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (comp[i][j] == -1 && grid[i][j] == 'X') {
                cc.emplace_back();
                dfs_for_connected_component(i, j);
                CONNECTED_COMPONENT_COUNT++;
            }
        }
    }
    dist.resize(cc.size());
    for (int i = 0; i < cc.size(); i++) {
        dist[i].assign(cc.size(), INF);
    }
    for (int i = 0; i < cc.size(); i++) {
        update_distances(i);
    }
    int vis[(1 << cc.size())][cc.size()];
    for (int i = 0; i < (1 << cc.size()); i++) {
        for (int j = 0; j < cc.size(); j++) {
            vis[i][j] = (int)1e9;
        }
    }
    for (int i = 0; i < (1 << cc.size()); i++) {
        for (int j = 0; j < cc.size(); j++) {
            if (i == 0) {
                vis[i][j] = 0;
            }
            for (int nxt = 0; nxt < cc.size(); nxt++) {
                if (!(i & (1 << nxt))) {
                    vis[i + (1 << nxt)][nxt] = min(vis[i + (1 << nxt)][nxt], vis[i][j] + dist[j][nxt]);
                }
            }
        }
    }
    int myMin = 1e9;
    for (int i = 0; i < cc.size(); i++) {
        myMin = min(myMin, vis[(1 << cc.size()) - 1][i]);
    }
    cout << myMin;
}
