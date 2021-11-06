#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
struct Node {
    bool gravity; //false -> down; true -> up
    int x;
    int y;
    bool operator== (const Node&n1) const{
        return (n1.x == x && n1.y == y && n1.gravity == gravity);
    }
    bool operator!= (const Node& n1) const{
        return !(n1.x == x && n1.y == y && n1.gravity == gravity);
    }
};
int main() {
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    char arr[n][m];
    Node start, end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == 'C') start = {false, i, j};
            else if (c == 'D') end = {false, i, j}; //danger
            arr[i][j] = c;
        }
    }
    bool hasVisited[n][m][2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            hasVisited[i][j][0] = hasVisited[i][j][1] = false;
        }
    }
    deque<pair<int, Node>> q;
    q.push_back(make_pair(0, start));
    while(!q.empty()) {
        Node cur = q.front().second;
        int dist = q.front().first;
        q.pop_front();
        if (cur.x < 0 || cur.y < 0 || cur.x == n || cur.y == m || hasVisited[cur.x][cur.y][cur.gravity] || arr[cur.x][cur.y] == '#') {
            continue;
        }
        if (cur.x == end.x && cur.y == end.y) {
            cout << dist << endl;
            return 0;
        }
        hasVisited[cur.x][cur.y][cur.gravity] = true;
        if (cur.gravity) {
            if (cur.x == 0 || arr[cur.x - 1][cur.y] != '#') {
                q.push_front(make_pair(dist, (Node){cur.gravity, cur.x - 1, cur.y}));
                continue;
            }
        } else {
            if (cur.x == n - 1 || arr[cur.x + 1][cur.y] != '#') {
                q.push_front(make_pair(dist, (Node){cur.gravity, cur.x + 1, cur.y}));
                continue;
            }
        }
        //try not flipping the direction of gravity (we can go left or right)
        q.push_front(make_pair(dist, (Node){cur.gravity, cur.x, cur.y + 1}));
        q.push_front(make_pair(dist, (Node){cur.gravity, cur.x, cur.y - 1}));
        //or we can change the direction of gravity
        q.push_back(make_pair(dist + 1, (Node){!cur.gravity, cur.x, cur.y}));
    }
    cout << "-1";
}
