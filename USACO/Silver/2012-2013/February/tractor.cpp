#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#pragma GCC optimize("O3")


#define ll int
using namespace std;
vector<vector<int>> grid;
vector<vector<int>> color;
void print(vector<vector<int>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
int cnt = 0;
void dfs (pair<int,int> curNode, int col, int dist) {
    color[curNode.first][curNode.second] = col;
    cnt++;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) == 1) {
                pair<int,int> new_pair = make_pair(dx + curNode.first, dy + curNode.second);
                if (new_pair.first < 0 || new_pair.second < 0 || new_pair.first == grid.size() || new_pair.second == grid.size()) {
                    continue;
                }
                if (color[new_pair.first][new_pair.second] != -1) {
                    continue;
                }
                if (abs(grid[new_pair.first][new_pair.second] - grid[curNode.first][curNode.second]) > dist) {
                    continue;
                }
                dfs(new_pair, col, dist);
            }
        }
    }
}
bool valid(int dist) {
    cnt = 0;
    color.resize(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        color[i].resize(grid.size());
        for (int j = 0; j < grid.size(); j++) {
            color[i][j] = -1;
        }
    }
    int cntr = 1;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (color[i][j] != -1) {
                continue;
            }
            cnt = 0;
            dfs({i, j}, cntr, dist);
            if (cnt >= (grid.size() * grid.size() + 1)/2) {
                return true;
            }
            cntr++;
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    int n;
    cin >> n;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    int l = 0;
    int r = (int)1e6;
    while(l < r) {
        int mid = (l + r)/2;
        if (valid(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
}
