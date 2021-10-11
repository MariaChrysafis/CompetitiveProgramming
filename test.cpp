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
vector<string> arr;
vector<vector<int>> nearestRock;
int main(){
    //freopen("hamming.in", "r", stdin);
    int n, d;
    cin >> n >> d;
    queue<Node> q;
    //cout << "YES\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr.push_back(s);
    }
    //cout << "YES\n";
    nearestRock.resize(n);
    for (int i = 0; i < n; i++) {
        nearestRock[i].resize(n);
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
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) hv[i][j] = false;
    while(!q.empty()) {
        Node cur = q.front();
        //cout << cur.x << " " << cur.y << endl;
        q.pop();
        if (cur.dist > nearestRock[cur.x][cur.y] || hv[cur.x][cur.y]) {
            continue;
        }
        nearestRock[cur.x][cur.y] = cur.dist;
        hv[cur.x][cur.y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if(abs(i) + abs(j) == 1) {
                    Node nxt;
                    nxt.dist = cur.dist + 1;
                    nxt.x = i + cur.x;
                    nxt.y = j + cur.y;
                    if (nxt.x >= 0 && nxt.y >= 0 && nxt.y < n && nxt.x < n) {
                        q.push(nxt);
                    }
                }
            }
        }
    }
    //return 0;
    queue <Node> mq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Node b;
            b.x = i, b.y = j, b.dist = 0;
            if(arr[i][j] == 'S') {
                mq.push(b);
            }
        }
    }
    int nearestSource[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nearestSource[i][j] = -1;
        }
    }
    bool hasVisited[n][n];
    int mm[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            hasVisited[i][j] = false;
            mm[i][j] = -1;
        }
    }
    while(!mq.empty()) {
        Node cur = mq.front();
        mq.pop();
        if (cur.x < 0 || cur.y < 0 || cur.x >= n || cur.y >= n || hasVisited[cur.x][cur.y]) {
            continue;
        }
        mm[cur.x][cur.y] = cur.dist;
        nearestSource[cur.x][cur.y] = cur.dist;
        hasVisited[cur.x][cur.y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) + abs(j) == 1) {
                    Node nxt = cur;
                    nxt.dist++, nxt.x += i, nxt.y += j;
                    if (nearestSource[nxt.x][nxt.y] != -1) {
                        continue;
                    }
                    if ((nxt.dist - 1)/d >= nearestRock[nxt.x][nxt.y]) {
                        continue;
                    }
                    if(nxt.dist/d >= nearestRock[nxt.x][nxt.y]) {
                        mm[nxt.x][nxt.y] = nxt.dist - 1;
                        continue;
                    }
                    if (hasVisited[nxt.x][nxt.y]) continue;
                    mq.push(nxt);
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
    mq = {};
    vector<pair<int, pair<int,int>>> vec;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            valid[i][j] = false;
            if(mm[i][j] != -1) {
                Node n1;
                n1.x = i, n1.y = j, n1.dist = mm[i][j];
                mq.push(n1);
            }
        }
        //cout << endl;
    }
    while(!mq.empty()) {
        Node cur = mq.front();
        mq.pop();
        valid[cur.x][cur.y] = true;
        if (cur.dist == 0) {
            continue;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if(abs(dx) + abs(dy) == 1) {
                    //cout << dx << " " << dy << endl;
                    Node n1 = cur;
                    n1.x += dx, n1.y += dy;
                    n1.dist--;
                    mq.push(n1);
                    //cout << n1.x << " " << n1.y << " " << n1.dist << endl;
                    //valid[n1.x][n1.y] = true;
                }
            }
        }
    }
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //cout << valid[i][j] << " ";
            cntr += valid[i][j];
        }
        //cout << endl;
    }
    cout << cntr << endl;

}
