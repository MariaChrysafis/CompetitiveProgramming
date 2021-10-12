#include <vector>
#include <chrono>
#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,fma")

using namespace std;
using namespace std::chrono;

void solve() {
    queue<pair<int,int>> q;
    q.push({0, 0});
    int n;
    cin >> n;
    string s[2];
    cin >> s[0] >> s[1];
    bool hasVisited[2][n];
    for (int i = 0; i < n; i++) {
        hasVisited[0][i] = hasVisited[1][i] = false;
    }
    while(!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (hasVisited[p.first][p.second]) {
            continue;
        }
        //cout << p.first << " " << p.second << endl;
        hasVisited[p.first][p.second] = true;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (p.first + dx < 0 || p.second + dy < 0 || p.first + dx == 2 || p.second + dy == n) {
                    continue;
                }
                if (s[p.first + dx][p.second + dy] == '1') {
                    continue;
                }
                q.push({p.first + dx, p.second + dy});
            }
        }
    }
    if (hasVisited[1][n - 1]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
