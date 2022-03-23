#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
const int MOD = 1e9 + 7;
vector<int> parent;
vector<vector<int>> adj;
vector<vector<int>> children;
vector<int> dp[2];
void dfs (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode);
        }
    }
}
int dfs1 (int curNode, int taken) {
    //taken = 1 means that we consider curNode
    //taken = 0 means that we do not consider curNode
    if (dp[taken][curNode] != -1) {
        return dp[taken][curNode];
    }
    if (taken == 0) {
        //we do not take curNode (i.e. we don't pair it)
        dp[taken][curNode] = 0;
        for (int i: children[curNode]) {
            dp[taken][curNode] += max(dfs1(i, 0), dfs1(i, 1)); //do some pairing in subtrees
        }
    } else {
        //we do take curNode and pair it
        if (children.size() == 0) {
            return (dp[taken][curNode] = 0);
        }
        dp[taken][curNode] = 1;
        int pos = 0;
        int myMax = -(int)1e9;
        for (int i: children[curNode]) {
            int x = max(dfs1(i, 1), dfs1(i, 0));
            pos += x;
            myMax = max(myMax, dfs1(i, 0) - x);
        }
        pos += myMax;
        dp[taken][curNode] = pos + 1; //everything except for one subtree does optimal pairing
    }
    return dp[taken][curNode];
}
int main() {
    int n;
    cin >> n;
    adj.resize(n);
    parent.resize(n);
    children.resize(n);
    dp[0].resize(n), dp[1].resize(n);
    for (int i = 0; i < n; i++) {
        dp[0][i] = dp[1][i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            if (j != parent[i]) {
                children[i].push_back(j);
            }
        }
    }
    int a = dfs1(0, 0);
    int b = dfs1(0, 1);
    cout << max(a,b);
}
