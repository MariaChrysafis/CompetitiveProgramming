#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
using namespace std;
vector<vector<int>> grid;
vector<vector<bool>> waypoint;
bool isValid(int dist) {
    queue<pair<int,int>> q;
    bool hasVisited[waypoint.size()][waypoint[0].size()];
    for (int i = 0; i < waypoint.size(); i++) {
        for (int j = 0; j < waypoint[0].size(); j++) {
            hasVisited[i][j] = false;
        }
    }
    bool flag = false;
    for (int i = 0; i < waypoint.size(); i++) {
        for (int j = 0; j < waypoint[i].size(); j++) {
            if (waypoint[i][j]) {
                flag = true;
                q.push(make_pair(i, j));
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (hasVisited[p.first][p.second]) {
            continue;
        }
        hasVisited[p.first][p.second] = true;
        //cout << p.first << " " << p.second << endl;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) != 1) {
                    continue;
                }
                if (dx + p.first >= 0 && dx + p.first < waypoint.size() && dy + p.second >= 0 && dy + p.second < waypoint[0].size()) {
                    if (abs(grid[p.first][p.second] - grid[p.first + dx][p.second + dy]) <= dist) {
                        q.push(make_pair(p.first + dx, p.second + dy));
                    }
                }
            }
        }
    }
    for (int i = 0; i < waypoint.size(); i++) {
        for (int j = 0; j < waypoint[0].size(); j++) {
            if (waypoint[i][j] && !hasVisited[i][j]) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    grid.resize(N), waypoint.resize(N);
    for (int i = 0; i < N; i++) {
        grid[i].resize(M), waypoint[i].resize(M);
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            bool x;
            cin >> x;
            waypoint[i][j] = x;
        }
    }
    int l = 0;
    int r = (int)1e9;
    while (l < r) {
        int m = (l + r)/2;
        if (isValid(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << endl;
}
