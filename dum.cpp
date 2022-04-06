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
    vector<int> sub;
    int sz;
    map<pair<int,int>,int> weight;
public:

    void add_edge (int u1, int u2, int w) {
        adj[u1].push_back(u2), adj[u2].push_back(u1);
        weight[{u1, u2}] = weight[{u2, u1}] = w;
    }

    Tree (int n) {
        hasVisited.assign(n, false), adj.resize(n), sub.resize(n);
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

    map<pair<int,bool>,int> tot;
    vector<map<pair<int,bool>,int>> v;
    int64_t ans = 0;

    int centroid;

    void dfs1 (int curNode, int prevNode, int d, map<int,bool> m) {
        tot[{d, m[d]}]++;
        v.back()[{d, m[d]}]++;
        m[d] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                dfs1 (i, curNode, d + weight[{i, curNode}], m);
            }
        }
    }

    void solve (int curNode) {
        dfs (curNode, curNode);
        centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        tot.clear(), v.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                v.emplace_back(); map<int,bool> dum;
                dfs1 (i, centroid, weight[make_pair(i, centroid)], dum);
            }
        }
        int64_t res = 0;
        for (int i = 0; i < v.size(); i++) {
            for (auto& p: v[i]) {
                if (p.first.first != 0) {
                    for (int x = 1 - p.first.second; x <= 1; x++) {
                        res += p.second * (tot[{-p.first.first, x}] - v[i][{-p.first.first, x}]);
                    }
                } else {
                    for (int x = 0; x <= 1; x++) {
                        res += p.second * (tot[{-p.first.first, x}] - v[i][{-p.first.first, x}]);
                    }
                }
            }
        }
        assert(res % 2 == 0);
        ans += res/2 + tot[{0, 1}];
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve(i);
            }
        }
    }
};
int main () {
    //freopen("inp.txt", "r", stdin);
    //freopen("inp.txt", "r", stdin);
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
    myTree.solve(0);
    cout << myTree.ans << '\n';
}
