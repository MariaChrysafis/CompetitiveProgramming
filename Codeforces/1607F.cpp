#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
short int adj[2000][2000];
int n, m;
pair<int,int> nxt (pair<int,int> p) {
    char c = adj[p.first][p.second];
    if (c == 0) {
        p.first--;
    } else if (c == 1) {
        p.first++;
    } else if (c == 2) {
        p.second--;
    } else {
        p.second++;
    }
    if (p.first < 0 || p.second < 0 || p.first == n || p.second == m) {
        return {-1, -1};
    }
    return p;
}
int dp[2000][2000];
int vis[2000][2000];
int memoize (int x, int y) {
    if (nxt({x, y}) == make_pair(-1, -1)) {
        return (dp[x][y] = 1);
    }
    if (dp[x][y] != -1) {
        return dp[x][y];
    }
    dp[x][y] = memoize(nxt({x, y}).first, nxt({x, y}).second) + 1;
    return dp[x][y];
}
void solve(){
    cin >> n >> m;
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c;
            if (c == 'U') adj[i][j] = 0;
            else if (c == 'D') adj[i][j] = 1;
            else if (c == 'L') adj[i][j] = 2;
            else adj[i][j] = 3;
            dp[i][j] = -1;
            vis[i][j] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int id = m * i + j;
            pair<int,int> cur = {i, j};
            while (true) {
                vis[cur.first][cur.second] = id;
                cur = nxt(cur);
                if (cur == make_pair(-1, -1) || vis[cur.first][cur.second] != -1) {
                    break;
                }
            }
            pair<int,int> orig = cur;
            if (vis[cur.first][cur.second] == id && cur.first != -1) {
                vector<pair<int,int>> points;
                while (true) {
                    points.push_back(cur);
                    cur = nxt(cur);
                    if (cur == orig) {
                        break;
                    }
                }
                for (auto p: points) {
                    dp[p.first][p.second] = points.size();
                }
            }
        }
    }
    pair<int,int> best = {0, 0};
    int myMax = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = memoize(i, j);
            if (dp[i][j] > myMax) {
                myMax = dp[i][j];
                best = {i + 1, j + 1};
            }
        }
    }
    cout << best.first << " " << best.second << " " << myMax << '\n';
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
