#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> maze(n);
    vector<vector<bool>> hasVisited(n);
    vector<vector<pair<int,int>>> parent(n);
    pair<int,int> start, end;
    for (int i = 0; i < n; i++) {
        cin >> maze[i];
        hasVisited[i].resize(m);
        parent[i].resize(m);
        for (int j = 0; j < m; j++) {
            hasVisited[i][j] = false;
            parent[i][j] = {-1, -1};
            if (maze[i][j] == 'A') {
                start = {i, j};
            } else if (maze[i][j] == 'B') {
                end = {i, j};
            }
        }
    }
    queue<pair<pair<int,int>, pair<int,int>>> q;
    q.push({start, {-1, -1}});
    bool flag = false;
    while (!q.empty()) {
        pair<int,int> cur = q.front().first;
        pair<int,int> prev = q.front().second;
        q.pop();
        if (hasVisited[cur.first][cur.second]) {
            continue;
        }
        hasVisited[cur.first][cur.second] = true;
        parent[cur.first][cur.second] = prev;
        if (cur == end) {
            flag = true;
            break;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1) {
                    pair<int,int> nxt = {cur.first + dx, cur.second + dy};
                    if (nxt.first >= 0 && nxt.second >= 0 && nxt.first < n && nxt.second < m && maze[nxt.first][nxt.second] != '#') {
                        q.push(make_pair(make_pair(nxt.first, nxt.second), cur));
                    }
                }
            }
        }
    }
    if (!flag) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    vector<pair<int,int>> vec;
    pair<int,int> p = end;
    while (p.first != -1) {
        vec.push_back(p);
        p = parent[p.first][p.second];
    }
    reverse(vec.begin(), vec.end());
    cout << vec.size() - 1 << '\n';
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].first - vec[i - 1].first == 1) {
            cout << 'D';
        } else if (vec[i].first - vec[i - 1].first == -1) {
            cout << 'U';
        } else if (vec[i].second - vec[i - 1].second == -1) {
            cout << 'L';
        } else {
            cout << 'R';
        }
    }
}
