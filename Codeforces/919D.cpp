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
string s;
int memoize (int curNode, char c) {
    if (dp[curNode] != -1) {
        return dp[curNode];
    }
    dp[curNode] = (s[curNode] == c);
    for (int i: adj[curNode]) {
        dp[curNode] = max(dp[curNode], memoize(i, c) + (s[curNode] == c));
    }
    return dp[curNode];
}
int main() {
    int n, m;
    cin >> n >> m;
    cin >> s;
    adj.resize(n);
    vector<int> inDeg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        inDeg[v]++;
    }
    //check if contains cycle
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) {
            q.push(i);
        }
    }
    int cntr = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cntr++;
        for (int i: adj[x]) {
            inDeg[i]--;
            if (!inDeg[i]) {
                q.push(i);
            }
        }
    }
    if (cntr != n) {
        cout << "-1";
        return 0;
    }
    int myMax = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        dp.assign(n, -1);
        for (int i = 0; i < n; i++) {
            dp[i] = memoize(i, c);
            myMax = max(myMax, dp[i]);
        }
    }
    cout << myMax;
}
