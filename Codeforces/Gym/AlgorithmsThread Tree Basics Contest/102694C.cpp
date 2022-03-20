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
    int a, b, c;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    Tree myTree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.read();
    int Q;
    cin >> Q;
    vector<Query> vec(Q);
    for (int i = 0; i < Q; i++) {
        cin >> vec[i].a >> vec[i].b >> vec[i].c;
        vec[i].a--, vec[i].b--;
    }
    vector<int> dp = myTree.parent;
    for (int j = 31; j >= 0; j--) {
        int dm = j;
        dp = myTree.parent;
        while (dm--) {
            vector<int> new_dp = myTree.parent;
            for (int i = 0; i < dp.size(); i++) {
                new_dp[i] = dp[dp[i]];
            }
            dp = new_dp;
        }
        for (int i = 0; i < Q; i++) {
            if ((1 << j) <= vec[i].c && !myTree.isAncestor(dp[vec[i].a], vec[i].b)) {
                //cout << "GET " << dp[vec[i].a] << '\n';
                vec[i].c -= (1 << j);
                vec[i].a = dp[vec[i].a];
            }
        }
    }
    dp = myTree.parent;
    for (int i = 0; i < Q; i++) {
        if (vec[i].c == 0) {
            continue;
        }
        if (!myTree.isAncestor(vec[i].a, vec[i].b)) {
            vec[i].a = dp[vec[i].a];
            vec[i].c--;
        }
    }
    for (int i = 0; i < Q; i++) {
        if (vec[i].c == 0) {
            continue;
        }
        //cout << vec[i].a << " " << vec[i].b << " " << vec[i].c << '\n';
        if (abs(myTree.depth[vec[i].a] - myTree.depth[vec[i].b]) <= vec[i].c) {
            vec[i].c = 0;
            vec[i].a = vec[i].b = vec[i].b;
        } else {
            vec[i].c = abs(myTree.depth[vec[i].a] - myTree.depth[vec[i].b]) - vec[i].c;
            swap(vec[i].a, vec[i].b);
        }
    }
    for (int j = 31; j >= 0; j--) {
        int dm = j;
        dp = myTree.parent;
        while (dm--) {
            vector<int> new_dp = myTree.parent;
            for (int i = 0; i < dp.size(); i++) {
                new_dp[i] = dp[dp[i]];
            }
            dp = new_dp;
        }
        for (int i = 0; i < Q; i++) {
            if ((1 << j) <= vec[i].c && !myTree.isAncestor(dp[vec[i].a], vec[i].b)) {
                vec[i].c -= (1 << j);
                vec[i].a = dp[vec[i].a];
            }
        }
    }
    dp = myTree.parent;
    for (int i = 0; i < Q; i++) {
        if (vec[i].c == 0) {
            continue;
        }
        vec[i].a = dp[vec[i].a];
        vec[i].c--;
    }
    for (int i = 0; i < Q; i++) {
        cout << vec[i].a + 1 << '\n';
    }
}
