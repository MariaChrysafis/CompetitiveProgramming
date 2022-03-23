#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define ll long long
using namespace std;
struct tree{
    vector<vector<ll>> adj;
    vector<ll> depth, sub, parent, val;
    ll dfs (int curNode, int prevNode) {
        sub[curNode] = 1;
        parent[curNode] = prevNode;
        for (ll i: adj[curNode]) {
            if (i == prevNode) continue;
            sub[curNode] += dfs(i, curNode);
        }
        return sub[curNode];
    }
    ll memoize (int curNode) {
        if (val[curNode] != -1) {
            return val[curNode];
        }
        if (curNode == 0) {
            ll ans = 0;
            for (int i: depth) {
                ans += i;
            }
            return (val[curNode] = ans);
        }
        return (val[curNode] = memoize(parent[curNode]) + adj.size() - 2 * sub[curNode]);
    }
    void read (){
        int n = adj.size();
        depth.assign(n, 0);
        sub.assign(n, 0);
        parent.assign(n, 0);
        val.assign(n, -1);
        queue<pair<int,int>> q;
        q.push({0, 0});
        vector<bool> hasVisited;
        hasVisited.assign(n, false);
        while (!q.empty()) {
            int curNode = q.front().first;
            int curDist = q.front().second;
            q.pop();
            if (hasVisited[curNode]) continue;
            hasVisited[curNode] = true;
            depth[curNode] = curDist;
            for (int i: adj[curNode]) {
                q.push({i, curDist + 1});
            }
        }
        dfs(0, -1);
        for (int i = 0; i < n; i++) {
            memoize(i);
        }
    }
};
tree t;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout << corrupted("<()<>>");
    int n;
    cin >> n;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read();
    for (ll i: t.val) {
        cout << i << ' ';
    }
 
}
