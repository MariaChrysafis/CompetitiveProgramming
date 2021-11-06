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
struct node {
    int locx, locy; //location
    int dirx, diry; //direction
};
node rotate1 (node n) {
    swap(n.dirx, n.diry);
    n.diry = -n.diry;
    return n;
}
node rotate2 (node n) {
    node n1 = rotate1(n);
    n1.dirx = -n1.dirx, n1.diry = -n1.diry;
    return n1;
}
vector<string> grid;
int N;
node forward (node n) {
    node n1 = {n.locx + n.dirx, n.locy + n.diry, n.dirx, n.diry};
    if (n.locx == 0 && n.locy == N - 1) {
        return n;
    }
    if (n1.locx < 0 || n1.locy < 0 || n1.locx == N || n1.locy == N || grid[n1.locx][n1.locy] == 'H') {
        return n;
    }
    return n1;
}
struct Node {
    node bessie;
    node elsie;
    int dist;
};
int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);
    cin >> N;
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    queue<Node> q;
    node n1 = {N - 1, 0, -1, 0};
    node n2 = {N - 1, 0, 0, 1};
    q.push({n1, n2, 0});
    bool myMap[N][N][N][N][4];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    for (int a = 0; a < 4; a++) {
                        myMap[i][j][k][l][a] = false;
                    }
                }
            }
        }
    }
    map<pair<int,int>,int> m;
    m[{-1, 0}] = 3;
    m[{1, 0}] = 1;
    m[{0, -1}] = 2;
    m[{0, 1}] = 0;
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        if (myMap[cur.bessie.locx][cur.bessie.locy][cur.elsie.locx][cur.elsie.locy][m[{cur.bessie.dirx, cur.bessie.diry}]]) {
            continue;
        }
        //cout << cur.bessie.locx << " " << cur.bessie.locy << " " << cur.elsie.locx << " " << cur.elsie.locy << endl;
        myMap[cur.bessie.locx][cur.bessie.locy][cur.elsie.locx][cur.elsie.locy][m[{cur.bessie.dirx, cur.bessie.diry}]] = true;
        if (cur.elsie.locx == 0 && cur.elsie.locy == N - 1 && cur.bessie.locx == 0 && cur.bessie.locy == N - 1) {
            cout << cur.dist;
            return 0;
        }
        Node nxt1 = (Node){rotate1(cur.bessie), rotate1(cur.elsie), cur.dist + 1};
        Node nxt2 = (Node){rotate2(cur.bessie), rotate2(cur.elsie), cur.dist + 1};
        Node nxt3 = (Node){forward(cur.bessie), forward(cur.elsie), cur.dist + 1};
        q.push(nxt1), q.push(nxt2), q.push(nxt3);
    }
}
