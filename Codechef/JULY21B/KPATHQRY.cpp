#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}

struct tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    vector<int> sub;
    vector<int> depth;
    vector<int> parent;
    int cntr = 1;
    int lg2;

    void dfsForDepth(int u, int prev) {
        if (u != 0) depth[u] = depth[prev] + 1;
        else depth[u] = 0;
        for (int i: adj[u]) {
            if(i != prev) {
                dfsForDepth(i, u);
            }
        }
    }
    void dfs(int u, int prev) {
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for (int i = 1; i <= lg2; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (int v: adj[u]) {
            if (v != prev) {
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }

    bool isAncestor(int u, int v) {
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }

    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }

    int dist(int u, int v) {
        if (leastCommonAncestor(u, v) == u || leastCommonAncestor(u, v) == v) return abs(depth[u] - depth[v]);
        else return depth[u] + depth[v] - 2 * depth[leastCommonAncestor(u, v)];
    }

    void read() {
        int n;
        cin >> n;
        lg2 = ceil(log2(n)) + 3;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        depth.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v), adj[v].push_back(u);
        }
        depth[0] = 0;
        dfsForDepth(0, -1);
        dfs(0, 0);
        int q;
        cin >> q;
        while (q--) {
            int sz;
            cin >> sz;
            vector<int> v(sz);
            for (int i = 0; i < sz; i++) {
                cin >> v[i];
                v[i]--;
            }
            int lca = v[0];
            for (int i = 1; i < sz; i++) {
                lca = leastCommonAncestor(lca, v[i]);
            }
            int myMax = -1;
            int ind1 = -1;
            for (int i = 0; i < v.size(); i++) {
                if(depth[v[i]] > myMax){
                    myMax = depth[v[i]];
                    ind1 = i;
                }
            }
            myMax = -1;
            int ind2 = -1;
            for (int i = 0; i < v.size(); i++) {
                if(dist(v[i], v[ind1]) + dist(v[i], lca) == dist(v[ind1], lca)){
                    continue;
                }
                if (depth[v[i]] > myMax) {
                    ind2 = i;
                    myMax = depth[v[i]];
                }
            }
            if(ind2 == -1){
                cout << "YES\n";
                continue;
            }
            bool fine = true;
            for(int i = 0; i < v.size(); i++){
                if(dist(v[i], v[ind1]) + dist(v[i], v[ind2]) != dist(v[ind1], v[ind2])){
                    fine = false;
                    break;
                }
            }
            if(fine) cout << "YES\n";
            else cout << "NO\n";
        }
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        tree myTree;
        myTree.read();
    }
}
