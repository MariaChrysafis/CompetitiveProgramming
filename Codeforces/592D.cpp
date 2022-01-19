#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;

class Tree {
public:
    vector<vector<int>> adj;
    vector<bool> needVisit;
    vector<int> sub;
    vector<int> depth;

    Tree(int n) {
        adj.resize(n);
        needVisit.assign(n, false);
        sub.resize(n);
        depth.resize(n);
    }

    void dfs_parent (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs_parent(i, curNode);
            }
        }
    }

    int dfs_sub (int curNode, int prevNode) {
        sub[curNode] = needVisit[curNode];
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                sub[curNode] += dfs_sub(i, curNode);
            }
        }
        return sub[curNode];
    }

    void dfs_depth (int curNode, int prevNode) {
        if (prevNode != -1) depth[curNode] = depth[prevNode] + 1;
        else depth[curNode] = 0;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs_depth(i, curNode);
            }
        }
    }

    bool okay (int x) {
        if (needVisit[x]) {
            return true;
        }
        return sub[x];
    }

    void read () {
        for (int i = 0; i < needVisit.size(); i++) {
            if (needVisit[i]) {
                dfs_sub(i, -1);
                break;
            }
        }
    }

    void resz () {
        vector<vector<int>> new_adj(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            for (int j: adj[i]) {
                if (needVisit[i] && needVisit[j]) {
                    new_adj[i].push_back(j);
                }
            }
        }
        adj = new_adj;
    }
    int cntr = 0;
    void dfs (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
                cntr ++;
            }
        }
        cntr++;
    }

    int find_farthest_point (int x) const {
        queue<pair<int,int>> q;
        q.push({x, 0});
        map<int,int> dist;
        map<int,bool> hasVisited;
        while (!q.empty()) {
            pair<int,int> p = q.front();
            q.pop();
            if (hasVisited[p.first]) {
                continue;
            }
            hasVisited[p.first] = true;
            dist[p.first] = p.second;
            //cout << p.first << " " << p.second << '\n';
            for (int i: adj[p.first]) {
                q.push({i, p.second + 1});
            }
        }
        int pnt = -1;
        dist[-1] = -1;
        for (auto& p: hasVisited) {
            if (dist[pnt] < dist[p.first]) {
                pnt = p.first;
            }
        }
        return pnt;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    Tree t = Tree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        x--;
        t.needVisit[x] = true;
    }
    t.read();
    for (int i = 0; i < N; i++) {
        t.needVisit[i] = t.okay(i);
    }
    t.resz();
    int x = -1;
    for (int i = 0; i < N; i++) {
        if (t.needVisit[i]) {
            x = t.find_farthest_point(i);
            break;
        }
    }
    int y = t.find_farthest_point(x);
    cout << min(x, y) + 1 << '\n';
    t.dfs(min(x, y), -1);
    t.dfs_depth(min(x, y), -1);
    cout << t.cntr - 1 -t.depth[max(x,y)] +t.depth[min(x,y)] << '\n';
}
