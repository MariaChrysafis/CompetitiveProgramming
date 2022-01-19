#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;

vector<vector<ll>> _adj;
vector<ll> _val;
class Tree {
public:
    vector<vector<ll>> adj;
    vector<ll> val, parent;
    vector<vector<ll>> dp;
    Tree (int bit) {
        adj = _adj;
        val = _val;
        for (int i = 0; i < val.size(); i++) {
            val[i] = (bool)((1 << bit) & val[i]);
        }
        dp.resize(adj.size()), parent.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            dp[i].assign(2, -1);
        }
    }
    void dfs (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        dp[curNode][val[curNode]] = 1;
        dp[curNode][!val[curNode]] = 0;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
                dp[curNode][val[curNode]] += dp[i][0];
                dp[curNode][!val[curNode]] += dp[i][1];
            }
        }
    }
    ll read () {
        ll ans = 0;
        for (int i = 0; i < adj.size(); i++) {
            vector<int> children;
            for (int j: adj[i]) {
                if (j == parent[i]) {
                    continue;
                }
                children.push_back(j);
            }
            ll o[2] = {0, 0};
            for (int x1: children) {
                o[1] += dp[x1][1];
                o[0] += dp[x1][0];
            }
            if (val[i]) {
                ll res = 0;
                res += o[0] * o[0] + o[1] * o[1];
                for (int x1: children) {
                    res -= dp[x1][0] * dp[x1][0];
                    res -= dp[x1][1] * dp[x1][1];
                }
                res /= 2;
                ans += res;
            } else {
                ll res = 0;
                res += o[0] * o[1];
                for (int x1: children) {
                    res -= dp[x1][0] * dp[x1][1];
                }
                ans += res;
            }
            ans += dp[i][1];
        }
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    _val.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> _val[i];
    }
    _adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        _adj[u].push_back(v), _adj[v].push_back(u);
    }
    ll ans = 0;
    ll powr = 1;
    for (int i = 0; i <= 20; i++) {
        Tree myTree(i);
        myTree.dfs(0, -1);
        ll x = myTree.read();
        ans += x * powr;
        powr *= 2;
    }
    cout << ans;
}
