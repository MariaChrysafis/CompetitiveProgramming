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
int64_t M;
int64_t phi;
int64_t inv;
vector<int64_t> powr_inv, powr_base;
int64_t binPow (int64_t x, int64_t y) {
    int64_t res = x;
    int64_t ans = 1;
    while (y) {
        if (y & 1) {
            ans *= res, ans %= M;
        }
        res *= res;
        res %= M;
        y /= 2;
    }
    return ans;
}
class Tree {
public:
    vector<vector<int>> adj;
    vector<bool> hasVisited;
    vector<int> sub;
    map<pair<int,int>, int64_t> weight;
    vector<int> w, parent;
    int sz;
    int get_weight (int u1, int u2) {
        return (parent[u1] == u2 ? w[u1]: w[u2]);
    }
    void propagate (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        w[curNode] = weight[{curNode, prevNode}];
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                propagate(i, curNode);
            }
        }
    }
    void dfs1 (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (!hasVisited[i] && i != prevNode) {
                dfs1 (i, curNode), sub[curNode] += sub[i];
            }
        }
        sz = sub[curNode];
    }
    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i] && sub[i] > sz/2) {
                return get_centroid (i, curNode);
            }
        }
        return curNode;
    }
    map<int,int> tot1, tot2, v1, v2;
    int64_t res = 0;
    void dfs (int curNode, int prevNode, int64_t d, int64_t d1, int64_t d2) {
        d1 %= M, d2 %= M;
        res += (d1 == 0);
        res += (d2 == 0);
        v1[d1]++, tot1[d1]++;
        v2[d2]++, tot2[d2]++;
        ans += tot2[((M - d1) * powr_inv[d]) % M] - v2[((M - d1) * powr_inv[d]) % M];
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i]) {
                int we = get_weight(i, curNode);
                dfs (i, curNode, d + 1, 10 * d1 + we, powr_base[d] * we + d2);
            }
        }
    }
    int64_t ans = 0;
    void solve (int curNode) {
        dfs1(curNode, curNode);
        if (sz == 1) {
            return;
        }
        int centroid = get_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        tot1.clear(), tot2.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                v1.clear(), v2.clear();
                dfs (i, i, 1, get_weight(i, centroid), get_weight(i, centroid));
            }
        }
        tot1.clear(), tot2.clear();
        reverse(adj[centroid].begin(), adj[centroid].end());
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                v1.clear(), v2.clear();
                dfs (i, i, 1, get_weight(i, centroid), get_weight(i, centroid));
            }
        }
        ans += res/2;
        res = 0;
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve(i);
            }
        }
    }
    Tree (int n) {
        adj.resize(n);
        sub.resize(n);
        hasVisited.assign(n, false);
        w.resize(n), parent.resize(n);
    }
};

int Phi (int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N >> M;
    powr_inv = powr_base = {1};
    phi = Phi(M);
    inv =  binPow(10, phi - 1);
    while (powr_inv.size() != N + 10) {
        powr_inv.push_back(powr_inv.back() * inv);
        powr_base.push_back(powr_base.back() * 10);
        powr_base.back() %= M, powr_inv.back() %= M;
    }
    Tree myTree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w; w %= M;
        myTree.adj[u].push_back(v), myTree.adj[v].push_back(u);
        myTree.weight[{u, v}] = myTree.weight[{v, u}] = w;
    }
    myTree.propagate(0, -1);
    myTree.solve(0);
    cout << myTree.ans;
}
