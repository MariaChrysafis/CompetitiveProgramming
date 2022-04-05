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
    vector<bool> hasVisited;
 
    Tree (int n, int K) {
        adj.resize(n), sub.resize(n), this->k = K;
        hasVisited.assign(n, false);
    }
 
    void dfs1 (int curNode, int prevNode, int depth) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode) dfs1(i, curNode, depth + 1), sub[curNode] += sub[i];
        sz = sub[curNode];
    }
 
    vector<vector<int>> vec;
    vector<vector<int>> v;
    vector<int> tot;
 
    void dfs2 (int curNode, int prevNode, int depth) {
        if (vec.back().size() == depth) vec.back().push_back(0);
        vec.back()[depth]++;
        if (tot.size() == depth) tot.push_back(0);
        tot[depth]++;
        v.back().push_back(depth);
        for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode) dfs2(i, curNode, depth + 1);
    }
 
    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode && sub[i] >= sz/2) return get_centroid(i, curNode);
        return curNode;
    }
 
    int k;
 
    int64_t solve (int curNode) {
        dfs1(curNode, curNode, 0);
        if (sz == 1) return 0;
        int centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        int64_t ans = 0;
        vec.clear(), tot.clear(), v.clear();
        for (int i: adj[centroid]) if (!hasVisited[i]) v.emplace_back(), vec.emplace_back(), dfs2(i, i, 0);
        for (int i = 1; i < tot.size(); i++) tot[i] += tot[i - 1];
        for (int i = 0; i < vec.size(); i++) for (int j = 1; j < vec[i].size(); j++) vec[i][j] += vec[i][j - 1];
        if (k - 1 >= 0) ans += tot[min(k - 1, (int)tot.size() - 1)];
        int64_t res = 0;
        for (int j = 0; j < vec.size(); j++) for (int i: v[j]) if (k - 2 - i >= 0) res += (int64_t)tot[min(k - 2 - i, (int)tot.size() - 1)] - vec[j][min(k - 2 - i, (int)vec[j].size() - 1)];
        ans += res/2;
        for (int i: adj[centroid]) if (!hasVisited[i]) ans += solve(i);
        return ans;
    }
 
    void add_edge (int u1, int u2) {
        adj[u1].push_back(u2), adj[u2].push_back(u1);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K1, K2;
    cin >> N >> K1 >> K2;
    Tree myTree(N, K2); Tree myTree1(N, K1 - 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v), myTree1.add_edge(u, v);
    }
    cout << myTree.solve(0) - myTree1.solve(0);
 
}
