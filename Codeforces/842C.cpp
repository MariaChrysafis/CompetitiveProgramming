#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
int gcd (int x, int y) {
    if (!x || !y) return max(x,y);
    return gcd(max(x,y) % min(x,y), min(x,y));
}
vector<vector<int>> adj;
vector<int> parent, dp, arr;
vector<int> dpG; //how many things from 1...i have a gcd which is a multiple of g
void find_parent (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            find_parent(i, curNode);
        }
    }
}
int memoize (int curNode) {
    if (dp[curNode] != -1) return dp[curNode];
    if (curNode == 0) return (dp[0] = 0);
    return dp[curNode] = gcd(memoize(parent[curNode]), arr[curNode]);
}

int dfs (int curNode, int g) {
    if (dpG[curNode] != -1) return dpG[curNode];
    if (curNode == 0) return (dpG[curNode] = 0);
    return (dpG[curNode] = dfs(parent[curNode], g) + (arr[curNode] % g != 0));
}

int main() {
    int n;
    cin >> n;
    adj.resize(n), arr.resize(n);
    parent.assign(n, 0), dp.assign(n, -1), dpG.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    find_parent(0, -1);
    for (int i = 0; i < n; i++) {
        memoize(i);
    }
    set<int> factors;
    for (int i = 1; i <= sqrt(arr[0]); i++) {
        if (arr[0] % i == 0) {
            factors.insert(i);
            factors.insert(arr[0] / i);
        }
    }
    for (int i: factors) {
        dpG.assign(n, -1);
        for (int j = 0; j < n; j++) {
            dfs(j, i);
        }
        for (int j = 0; j < n; j++) {
            if (dpG[j] <= 1) {
                dp[j] = max(dp[j], i);
            }
        }
    }
    for (int i = 0; i < dp.size(); i++) {
        cout << dp[i] << ' ';
    }
}
