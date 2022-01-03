#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
struct tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    vector<int> depth, sub, parent;
    int cntr = 1;
    int lg2;
    void dfs (int u, int prev){
        parent[u] = prev;
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    bool isAncestor(int u, int v){
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    int leastCommonAncestor(int u, int v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(int i = lg2; i >= 0; i--){
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    int goUp (int curNode, int dist) {
        if (dist == 0) return curNode;
        int lg2 = log2(dist);
        return goUp(dp[curNode][lg2], dist - (1 << lg2));
    }
    int dist (int u, int v) {
        return depth[u] + depth[v] - 2 * depth[leastCommonAncestor(u, v)];
    }
    int mem (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                sub[curNode] += mem(i, curNode);
            }
        }
        return sub[curNode];
    }
    void read (){
        int n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
        queue<pair<int,int>> q;
        q.push({0, 0});
        depth.assign(adj.size(), 1e9);
        while (!q.empty()) {
            int curNode = q.front().first;
            int curDist = q.front().second;
            q.pop();
            if (depth[curNode] != 1e9) {
                continue;
            }
            depth[curNode] = curDist;
            for (int i: adj[curNode]) {
                q.push({i, curDist + 1});
            }
        }
        sub.assign(adj.size(), 0);
        mem(0, -1);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    tree t;
    int N;
    cin >> N;
    t.adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read();
    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u == v) {
            cout << N << '\n';
            continue;
        }
        if (t.depth[u] > t.depth[v]) {
            swap(u, v);
        }
        if (t.depth[u] % 2 != t.depth[v] % 2) {
            cout << 0 << '\n';
            continue;
        }
        //if (t.depth[u] == t.depth[v])
        int mid = t.goUp(v, t.dist(u, v)/2);
        int ans = t.sub[mid];
        if (t.leastCommonAncestor(mid, u) == mid) {
            int distance = t.dist(mid, u);
            ans -= t.sub[t.goUp(u, distance - 1)];
        }
        if (t.leastCommonAncestor(mid, v) == mid) {
            int distance = t.dist(mid, v);
            ans -= t.sub[t.goUp(v, distance - 1)];
        }
        if (t.depth[u] == t.depth[v]) {
            ans += t.adj.size() - t.sub[mid];
        }
        cout << ans << '\n';
    }
}
