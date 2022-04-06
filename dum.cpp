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
    vector<vector<int>> adj;
    vector<bool> hasVisited;
    vector<int> sub, parent;
    int sz;
    map<pair<int,int>,int> weight;
    vector<int> wei;
public:

    int get_weight (int u1, int u2) {
        //assert((parent[u1] != u2) ? wei[u2] : wei[u1] == weight[make_pair(u1, u2)]);
        return ((parent[u1] != u2) ? wei[u2] : wei[u1]);
    }

    void propagate (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        if (weight.count({curNode, prevNode})) {
            wei[curNode] = weight[{curNode,prevNode}];
        }
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                propagate(i, curNode);
            }
        }
    }

    void add_edge (int u1, int u2, int w) {
        adj[u1].push_back(u2), adj[u2].push_back(u1);
        weight[{u1, u2}] = weight[{u2, u1}] = w;
    }

    Tree (int n) {
        hasVisited.assign(n, false), adj.resize(n), sub.resize(n), wei.resize(n), parent.resize(n);
    }

    int dfs (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                sub[curNode] += dfs (i, curNode);
            }
        }
        return (sz = sub[curNode]);
    }

    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                if (sub[i] > sz/2) {
                    return get_centroid(i, curNode);
                }
            }
        }
        return curNode;
    }

    map<int,int> tot[2];
    map<int,int> v[2];
    int64_t ans = 0;

    int centroid;

    void dfs1 (int curNode, int prevNode, int d, int l, int r) {
        bool b = (d >= l && d <= r && r > l);
        l -= (d < l);
        r += (d > r);
        tot[b][d]++;
        v[b][d]++;
        for (int x = ((d == 0) ? 0 : 1 - b); x <= 1; x++) {
            ans += (tot[x][-d] - v[x][-d]);
        }
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                dfs1 (i, curNode, d + get_weight(i, curNode), l, r);
            }
        }
    }

    void solve (int curNode) {
        dfs (curNode, curNode);
        centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        tot[0].clear(), v[0].clear(), tot[1].clear(), v[1].clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                v[0].clear(), v[1].clear();
                dfs1 (i, centroid, get_weight(i, centroid), get_weight(i, centroid), get_weight(i, centroid));
            }
        }
        ans += tot[1][0];
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve(i);
            }
        }
    }
};
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);
    int n;
    cin >> n;
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        myTree.add_edge(u, v, w - (w == 0));
    }
    myTree.propagate(0, 0);
    myTree.solve(0);
    cout << myTree.ans << '\n';
}
