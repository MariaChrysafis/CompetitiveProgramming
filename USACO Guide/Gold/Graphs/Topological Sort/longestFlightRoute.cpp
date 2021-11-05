#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
 
using namespace std;
 
vector<vector<int>> adj;
vector<int> dp;
vector<int> parent;
int memoize (int x) {
    if (dp[x] != -1) {
        return dp[x];
    }
    dp[x] = -(int)1e8;
    for (int i: adj[x]) {
        if (dp[x] < memoize(i) + 1) {
            parent[x] = i;
            dp[x] = memoize(i) + 1;
        }
    }
    return dp[x];
}
int main() {
    int n, m;
    cin >> n >> m;
    dp.assign(n, -1);
    parent.assign(n, -1);
    adj.resize(n);
    vector<int> inDeg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }
    dp[n - 1] = 0;
    for (int i = 0; i < n; i++) {
        memoize(i);
    }
    if (dp[0] < 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    int best = 0;
    vector<int> v;
    while (best != -1) {
        v.push_back(best + 1);
        best = parent[best];
    }
    cout << v.size() << endl;
    for (int i: v) {
        cout << i << " ";
    }
}
