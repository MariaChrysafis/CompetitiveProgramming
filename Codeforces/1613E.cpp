#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
const int MOD = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    string arr[n];
    pair<int,int> start;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 'L') {
                start = {i, j};
            }
        }
    }
    set<pair<int,int>> neighbors[n][m];
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int dx: {-1, 0, 1}) {
                for (int dy: {-1, 0, 1}) {
                    if (abs(dx) + abs(dy) != 1) continue;
                    if (dx + x < 0 || dy + y < 0 || dx + x == n || dy + y == m) continue;
                    if (arr[x + dx][y + dy] != '.') continue;
                    neighbors[x][y].insert({x + dx, y + dy});
                }
            }
        }
    }
    queue<pair<int,int>> q;
    q.push(start);
    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();
        arr[cur.first][cur.second] = '+';
        for (auto& p: neighbors[cur.first][cur.second]) {
            neighbors[p.first][p.second].erase(cur);
            if (neighbors[p.first][p.second].size() <= 1) {
                q.push(p);
            }
        }
    }
    arr[start.first][start.second] = 'L';
    for (int i = 0; i < n; i++) {
        cout << arr[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
