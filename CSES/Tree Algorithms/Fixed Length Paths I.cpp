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
    Tree (int n, int K) {
        adj.resize(n), sub.resize(n), this->k = K;
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
 
    int k;
 
    int64_t solve (int curNode) {
        dfs1(curNode, curNode, 0);
        int centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        int64_t ans = 0;
        tot.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                d.clear(), dfs1(i, i, 0);
                for (int j = max(k - 1 - (int) tot.size(), 0); j <= min((int) d.size() - 1, k - 2); j++) {
                    if (k - 2 - j < d.size()) {
                        ans += (tot[k - 2 - j] - d[k - 2 - j]) * d[j];
                    } else {
                        ans += tot[k - 2 - j] * d[j];
                    }
                }
            }
        }
        if (k - 1 < tot.size()) {
            ans += tot[k - 1];
        }
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                ans += solve(i);
            }
        }
        return ans;
    }
 
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    Tree myTree(N, K);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    cout << myTree.solve(0);
 
}
