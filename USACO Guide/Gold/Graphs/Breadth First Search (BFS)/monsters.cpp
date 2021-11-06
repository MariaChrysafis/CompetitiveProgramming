#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
 
using namespace std;
struct Coord {
    int x, y;
    int dist;
};
struct Node {
    Coord c;
    Coord p;
    bool operator<(const Node& c1) const {
        if (c1.c.dist == c.dist) {
            return (make_pair(c.x, c.y) < make_pair(c1.c.x, c1.c.y));
        }
        return (c1.c.dist < c.dist);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    Node start;
    vector<Node> monsters;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                start = {{i, j, 0}, {-1,-1, 0}};
            } else if (grid[i][j] == 'M') {
                monsters.push_back({{i, j, 0}, {-1,-1, 0}});
            }
        }
    }
    queue<Node> pq;
    for (Node myNode: monsters) {
        pq.push(myNode);
    }
    vector<vector<int>> monster_dist(n), dist(n);
    vector<vector<Coord>> parent(n);
    for (int i = 0; i < n; i++) {
        monster_dist[i].assign(m, -2);
        dist[i].assign(m, -2);
        parent[i].assign(m, {-1, -1, 0});
    }
    while (!pq.empty()) {
        Node myNode = pq.front();
        Coord cur = myNode.c;
        pq.pop();
        if (monster_dist[cur.x][cur.y] != -2 || grid[cur.x][cur.y] == '#') {
            continue;
        }
        monster_dist[cur.x][cur.y] = cur.dist;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (cur.x + dx < 0 || cur.x + dx == n || cur.y + dy < 0 || cur.y + dy == m || abs(dx) + abs(dy) != 1) {
                    continue;
                }
                pq.push({cur.x + dx, cur.y + dy, cur.dist + 1});
            }
        }
    }
    for (int i = 0; i < monster_dist.size(); i++) {
        for (int j = 0; j < monster_dist[i].size(); j++) {
            if (monster_dist[i][j] == -2) {
                monster_dist[i][j] = (int)1e8;
            }
        }
    }
    pq.push(start);
    while (!pq.empty()) {
        Node myNode = pq.front();
        Coord cur = myNode.c;
        //cout << cur.x << " " << cur.y << endl;
        pq.pop();
        if (dist[cur.x][cur.y] != -2 || grid[cur.x][cur.y] == '#' || cur.dist >= monster_dist[cur.x][cur.y]) {
            continue;
        }
        parent[cur.x][cur.y] = myNode.p;
        dist[cur.x][cur.y] = cur.dist;
        if (cur.x == 0 || cur.y == 0 || cur.x ==  n - 1 || cur.y == m - 1) {
            cout << "YES\n";
            cout << cur.dist << endl;
            vector<Coord> vec;
            Coord soFar = cur;
            while (true) {
                vec.push_back(soFar);
                soFar = parent[soFar.x][soFar.y];
                if (soFar.x < 0) {
                    break;
                }
            }
            reverse(vec.begin(), vec.end());
            for (int i = 0; i < vec.size() - 1; i++) {
                if (abs(vec[i].x - vec[i + 1].x) == 1) {
                    if (vec[i].x > vec[i + 1].x) cout << 'U';
                    else cout << 'D';
                }
                if (abs(vec[i].y - vec[i + 1].y) == 1) {
                    if (vec[i].y > vec[i + 1].y) cout << 'L';
                    else cout << 'R';
                }
            }
            return 0;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (cur.x + dx < 0 || cur.x + dx == n || cur.y + dy < 0 || cur.y + dy == m || abs(dx) + abs(dy) != 1) {
                    continue;
                }
                pq.push({{cur.x + dx, cur.y + dy, cur.dist + 1}, {cur.x, cur.y, cur.dist}});
            }
        }
    }
    cout << "NO\n";
}
