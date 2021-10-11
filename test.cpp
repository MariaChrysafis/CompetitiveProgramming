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
struct Block {
    int x; //center (x, y)
    int y;
    int time;
    int size;
};
bool Compare(Node a1, Node a2)
{
    return (a1.dist < a2.dist);
}
string read() {
    string s;
    cin >> s;
    return s;
}
vector<string> arr;
vector<vector<int>> nearestRock;
int main(){
    //freopen("hamming.in", "r", stdin);
    int n, d;
    cin >> n >> d;
    d = min(d, 2 * n + 4);
    nearestRock.resize(n);
    queue<Node> q;
    for (int i = 0; i < n; i++) {
        nearestRock[i].resize(n);
        for (int j = 0; j < n; j++) {
            nearestRock[i][j] = n + n;
        }
        arr.push_back(read());
        for (int j = 0; j < n; j++) {
            if(arr[i][j] == '#') {
                Node cur;
                cur.x = i, cur.y = j, cur.dist = 0;
                q.push(cur);
            }
        }
    }
    while(!q.empty()) {
        Node cur = q.front();
        q.pop();
        if (cur.dist > nearestRock[cur.x][cur.y]) {
            continue;
        }
        nearestRock[cur.x][cur.y] = cur.dist;
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
        if (cur.x < 0 || cur.y < 0 || cur.x >= n || cur.y >= n) {
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
                    //cout << nxt.x << " " << nxt.y << " " << nxt.dist/d << " " << nearestRock[nxt.x][nxt.y] << endl;
                    if ((nxt.dist - 1)/d >= nearestRock[nxt.x][nxt.y]) {
                        continue;
                    }
                    if(nxt.dist/d >= nearestRock[nxt.x][nxt.y]) {
                        mm[nxt.x][nxt.y] = nxt.dist - 1;
                        continue;
                    }
                    mq.push(nxt);
                }
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mm[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
     */
    //return 0;
    bool valid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            valid[i][j] = false;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mm[i][j] != -1) {
                valid[i][j] = true;
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < n; y++) {
                        if (abs(i - x) + abs(j - y) <= (mm[i][j])/d) {
                            valid[x][y] = true;
                        }
                    }
                }
            }
        }
        //cout << endl;
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
