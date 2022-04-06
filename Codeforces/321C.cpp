#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
class Tree {
protected:
    vector<int> sub;
public:
    int sz;
    vector<vector<int>> adj;
    vector<int64_t> tot;
    vector<bool> hasVisited;
    vector<int64_t> d;
    Tree (int n) {
        adj.resize(n), sub.resize(n), mark.resize(n);
        hasVisited.assign(n, false);
    }
    void dfs1 (int curNode, int prevNode, int depth) {
        sub[curNode] = 1;
        if (depth == d.size()) {
            d.push_back(0);
        }
        if (depth == tot.size()) {
            tot.push_back(0);
        }
        d[depth]++, tot[depth]++;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                dfs1(i, curNode, depth + 1), sub[curNode] += sub[i];
            }
        }
        sz = sub[curNode];
    }
    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode && sub[i] >= sz/2) {
                return get_centroid(i, curNode);
            }
        }
        return curNode;
    }

    vector<char> mark;


    void solve (int curNode, char depth) {
        dfs1(curNode, curNode, 0);
        int centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        mark[centroid] = depth;
        depth++;
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve(i, depth);
            }
        }
    }

    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
};
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.solve(0, 'A');
    //cout << myTree.ans << '\n';
    for (int i = 0; i < n; i++) {
        cout << myTree.mark[i] << ' ';
    }
}
