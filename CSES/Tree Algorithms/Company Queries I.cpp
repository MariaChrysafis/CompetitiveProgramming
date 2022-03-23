#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
class Tree {
    vector<vector<int>> adj;
public:
    Tree (int n) {
        adj.resize(n);
        depth.resize(n);
        parent.resize(n);
        pre.resize(n), post.resize(n);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> depth, pre, post, parent;
    int cntr = 0;
    void dfs (int curNode, int prevNode) {
        if (prevNode == -1) {
            depth[curNode] = 0;
        } else {
            depth[curNode] = depth[prevNode] + 1;
        }
        pre[curNode] = cntr++;
        parent[curNode] = max(prevNode, 0);
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        post[curNode] = cntr++;
    }
    bool isAncestor (int a, int b) {
        return (pre[a] <= pre[b] && post[a] >= post[b]);
    }
    void read () {
        dfs (0, -1);
    }
};
struct Query {
    int a, b;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    Tree myTree(N);
    for (int i = 1; i < N; i++) {
        int u; cin >> u; u--;
        myTree.add_edge(u, i);
    }
    myTree.read();
    vector<Query> vec(Q);
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].a >> vec[i].b;
        vec[i].a--;
    }
    vector<Query> orig = vec;
    for (int i = 31; i >= 0; i--) {
        int dm = i;
        vector<int> dp = myTree.parent;
        while (dm--) {
            vector<int> new_dp = myTree.parent;
            for (int j = 0; j < dp.size(); j++) {
                new_dp[j] = dp[dp[j]];
            }
            dp = new_dp;
        }
        for (int j = 0; j < vec.size(); j++) {
            if (vec[j].b & (1 << i)) {
                vec[j].b -= (1 << i);
                vec[j].a = dp[vec[j].a];
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        if (abs(myTree.depth[vec[i].a] - myTree.depth[orig[i].a]) == orig[i].b) {
            cout << vec[i].a + 1 << '\n';
        } else {
            cout << "-1\n";
        }
    }
 
}
