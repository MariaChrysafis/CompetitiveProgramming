#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

struct Tree {
    Tree(int n) {
        adj.resize(n);
        dp.assign(n, {0, 0, 0});
    }

    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs (int curNode, int prevNode) {
        vector<int> children;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
                children.push_back(i);
            }
        }
        if (children.empty()) { //leaf node!
            dp[curNode][0] = dp[curNode][1] = dp[curNode][2] = 0;
            return;
        } //it actually has children!
        for (int i: children) {
            dp[curNode][0] += max({dp[i][0], dp[i][1], dp[i][2]});
        }
        vector<int> delta;
        int sum = 0;
        for (int i: children) {
            delta.push_back(dp[i][1] + 1 - max({dp[i][0], dp[i][1], dp[i][2]}));
            sum += max({dp[i][0], dp[i][1], dp[i][2]});
        }
        sort(delta.begin(), delta.end());
        reverse(delta.begin(), delta.end());
        dp[curNode][1] = max(dp[curNode][1], sum + delta[0]);
        if (delta.size() >= 2) {
            dp[curNode][2] = max(dp[curNode][2], sum + delta[0] + delta[1]);
        }
    }

    vector<vector<int>> adj;
    vector<vector<int>> dp;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, x, y;
    cin >> n >> x >> y;
    Tree t(n);
    vector<int> deg;
    deg.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        deg[u - 1]++, deg[v - 1]++;
        t.add_edge(u - 1, v - 1);
    }
    t.dfs(0, -1);
    ll myMax = max({t.dp[0][0], t.dp[0][1], t.dp[0][2]});
    int leaf = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
            leaf++;
        }
    }
    if (x > y) {
        if (leaf >= n - 1) {
            cout << (n - 2) * y + x << '\n';
            return 0;
        }
        cout << (n - 1) * y << '\n';
        return 0;
    }
    cout << myMax * x + (n - 1 - myMax) * y;
}
