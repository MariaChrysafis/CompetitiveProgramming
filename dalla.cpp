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

    map<pair<int,pair<int,int>>,int> tot;
    vector<map<pair<int,pair<int,int>>,int>> v;

    void dfs1 (int curNode, int prevNode, int d, int sgn, int fst, int transitions) {
        //assert(transitions <= 1);
        tot[{d, {transitions, fst}}]++;
        v.back()[{d, {transitions, fst}}]++;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                assert(weight[make_pair(i, curNode)] != 0);
                transitions += (weight[make_pair(i, curNode)] != sgn);
                dfs1 (i, curNode, d + weight[{i, curNode}], weight[make_pair(i, curNode)], fst, min(transitions, 2));
                transitions -= (weight[make_pair(i, curNode)] != sgn);
            }
        }
    }

    int64_t solve (int curNode) {
        int64_t ans = 0;
        dfs (curNode, curNode);
        int centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        tot.clear(), v.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                v.emplace_back();
                dfs1 (i, i, weight[make_pair(i, centroid)], weight[make_pair(i, centroid)], weight[make_pair(i, centroid)], 0);
            }
        }
        int64_t res = 0;
        for (int i = 0; i < v.size(); i++) {
            for (auto& p: v[i]) {
                for (int x = 2 - p.first.second.first; x <= 2; x++) {
                    res += v[i][{p.first.first, {p.first.second.first, p.first.second.second}}] * (tot[{-p.first.first, {x, p.first.second.second}}] - v[i][{-p.first.first, {x, p.first.second.second}}]);
                }
                for (int x = 1 - p.first.second.first; x <= 2; x++) {
                    res += v[i][{p.first.first, {p.first.second.first, p.first.second.second}}] * (tot[{-p.first.first, {x, -p.first.second.second}}] - v[i][{-p.first.first, {x, -p.first.second.second}}]);
                }
            }
        }
        assert(res % 2 == 0);
        ans += res/2 + tot[{0, {2, -1}}] + tot[{0, {2, 1}}];
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                ans += solve(i);
            }
        }
        return ans;
    }
};
int main () {
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
    cout << myTree.solve(0) << '\n';
}
