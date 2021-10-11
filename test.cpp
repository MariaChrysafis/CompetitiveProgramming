#include <vector>
#include <chrono>
#include <iostream>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;
using namespace std::chrono;
struct Node {
    int x;
    int y;
    int dist;
};

struct nodeComparator {
    bool operator()(Node const &p1, Node const &p2) {
        return p1.dist < p2.dist;
    }
};

vector<string> arr;
vector<vector<int>> nearestRock;

int main() {
    int n, d;
    cin >> n >> d;
    queue<Node> q;
    nearestRock.resize(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr.push_back(s);
        nearestRock[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nearestRock[i][j] = n + n;
            if (arr[i][j] == '#') {
                Node cur;
                cur.x = i, cur.y = j, cur.dist = 0;
                q.push(cur);
            }
        }
    }
    bool hv[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            hv[i][j] = false;
        }
    }
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        if (cur.dist > nearestRock[cur.x][cur.y] || hv[cur.x][cur.y]) {
            continue;
        }
        nearestRock[cur.x][cur.y] = cur.dist;
        hv[cur.x][cur.y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) + abs(j) == 1) {
                    Node nxt = cur;
                    nxt.dist++, nxt.x += i, nxt.y += j;
                    if (nxt.x >= 0 && nxt.y >= 0 && nxt.y < n && nxt.x < n) {
                        q.push(nxt);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            hv[i][j] = false;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Node b;
            b.x = i, b.y = j, b.dist = 0;
            if (arr[i][j] == 'S') {
                q.push(b);
            }
        }
    }
    vector<vector<int>> nearestSource(n), mm(n);
    for (int i = 0; i < n; i++) {
        nearestSource[i].resize(n), mm[i].resize(n);
        for (int j = 0; j < n; j++) {
            nearestSource[i][j] = -1;
            mm[i][j] = -1;
        }
    }
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        if (cur.x < 0 || cur.y < 0 || cur.x >= n || cur.y >= n || hv[cur.x][cur.y]) {
            continue;
        }
        mm[cur.x][cur.y] = cur.dist;
        nearestSource[cur.x][cur.y] = cur.dist;
        hv[cur.x][cur.y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) + abs(j) == 1) {
                    Node nxt = cur;
                    nxt.dist++, nxt.x += i, nxt.y += j;
                    if (nearestSource[nxt.x][nxt.y] != -1 || hv[nxt.x][nxt.y] || (nxt.dist - 1) / d >= nearestRock[nxt.x][nxt.y]) {
                        continue;
                    }
                    if (nxt.dist / d >= nearestRock[nxt.x][nxt.y]) {
                        mm[nxt.x][nxt.y] = nxt.dist - 1;
                        continue;
                    }
                    q.push(nxt);
                }
            }
        }
    }
    bool valid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mm[i][j] != -1) {
                mm[i][j] /= d;
            }
        }
    }
    priority_queue<Node, vector<Node>, nodeComparator> mq;
    mq = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            valid[i][j] = false;
            if (mm[i][j] != -1) {
                Node n1;
                n1.x = i, n1.y = j, n1.dist = mm[i][j];
                mq.push(n1);
            }
        }
    }
    while (!mq.empty()) {
        Node cur = mq.top();
        mq.pop();
        if (valid[cur.x][cur.y]) {
            continue;
        }
        valid[cur.x][cur.y] = true;
        if (cur.dist == 0) {
            continue;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1) {
                    Node n1 = cur;
                    n1.x += dx, n1.y += dy, n1.dist--;
                    mq.push(n1);
                }
            }
        }
    }
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cntr += valid[i][j];
        }
    }
    cout << cntr << endl;

}
