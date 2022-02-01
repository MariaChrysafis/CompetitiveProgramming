#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <string>
#include <map>

using namespace std;
const int MAXN = 1e5 + 1;
struct Tree {
    vector<int> adj[MAXN];
    vector<int> dp[MAXN];
    int depth[MAXN];
    vector<int> comp;
    vector<pair<int,int>> diameter;
    void update_diameter (int x) {
        if (dist(diameter[comp[x]].first, x) > dist(diameter[comp[x]].first, diameter[comp[x]].second)) {
            diameter[comp[x]].second = x;
            return;
        }
        if (dist(diameter[comp[x]].second, x) > dist(diameter[comp[x]].first, diameter[comp[x]].second)) {
            diameter[comp[x]].first = x;
            return;
        }
    }
    void add (int new_node, int parent) {
        if (parent == -1) {
            comp.push_back(new_node);
            dp[new_node].assign(18, new_node);
            depth[new_node] = 0;
            diameter.emplace_back(new_node, new_node);
            return;
        }
        adj[new_node].push_back(parent), adj[parent].push_back(new_node);
        dp[new_node].resize(18);
        dp[new_node][0] = parent;
        for (int i = 1; i < dp[new_node].size(); i++) {
            dp[new_node][i] = dp[dp[new_node][i - 1]][i - 1];
        }
        depth[new_node] = depth[parent] + 1;
        comp.push_back(comp[parent]);
        update_diameter(new_node);
    }
    int goUp (int curNode, int x) {
        if (x == 0) {
            return curNode;
        }
        int lg2 = log2(x);
        return goUp(dp[curNode][lg2], x - (1 << lg2));
    }
    int dist (int u, int v) {
        return depth[u] + depth[v] - 2 * depth[leastCommonAncestor(u, v)];
    }
    bool isAncestor(int u, int v){
        if (depth[u] > depth[v]) {
            return false;
        }
        return (goUp(v, depth[v] - depth[u]) == u);
    }
    int leastCommonAncestor(int u, int v){
        if (isAncestor(u, v)){
            return u;
        }
        if (isAncestor(v, u)){
            return v;
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        v = goUp(v, depth[v] - depth[u]);
        for(int i = 17; i >= 0; i--){
            if (dp[u][i] != dp[v][i]) {
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        return dp[u][0];
    }
};
int main () {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Tree t;
    int Q;
    cin >> Q;
    int cntr = 0;
    while (Q--) {
        char c;
        cin >> c;
        if (c == 'B') {
            int p;
            cin >> p;
            t.add(cntr++, max(p - 1, -1));
        } else {
            int q;
            cin >> q;
            q--;
            cout << max(t.dist(t.diameter[t.comp[q]].first, q), t.dist(t.diameter[t.comp[q]].second, q)) << '\n';
        }
    }
}
