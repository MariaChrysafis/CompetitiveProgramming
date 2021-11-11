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
#define ll long long
#include <map>
using namespace std;
#define maxN 200001
const int INF = (int)1e8;
struct Tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> parent;
    vector<int> start, end;
    int cntr = 0;
    void memoize (int curNode, int prevNode) {
        start[curNode] = cntr++;
        parent[curNode] = prevNode;
        for (int i: adj[curNode]) {
            if (i == prevNode) {
                continue;
            }
            memoize(i, curNode);
        }
        end[curNode] = cntr++;
    }
    int isAncestor (int u, int v) {
        return (start[u] <= start[v] && end[u] >= end[v]);
    }
    int lca (int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = 19; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    void read(int src) {
        dp.resize(adj.size());
        parent.resize(adj.size());
        start.resize(adj.size()), end.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            dp[i].resize(20);
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] = 0;
            }
        }
        memoize(src, -1);
        for (int j = 0; j < 20; j++) {
            for (int i = 0; i < adj.size(); i++) {
                if (j == 0) {
                    dp[i][j] = parent[i];
                    if (dp[i][j] == -1) dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                }
            }
        }
    }
};
struct graph{
    vector<vector<pair<int,int>>> adj; //{-weight, node}
    vector<int> dijk(int src){
        vector<int> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = INF;
            mark[i] = false;
        }
        priority_queue<pair<int,int>> pq;
        dist[src] = 0, pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second; //node
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                int v = p.second;
                int w = p.first;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], v});
                }
            }
        }
        return dist;
    }
};
vector<vector<int>> adj;
Tree t;
pair<int,int> BFS(vector<int> src){
    bool hasVisited[maxN];
    for(int i = 0; i < maxN; i++) {
        hasVisited[i] = false;
    }
    queue<pair<int,int>> pq;
    if (src.size() == 2) {
        int u = src[0];
        int v = src[1];
        int lca = t.lca(u, v);
        src.clear();
        for (int i = 0; i < t.adj.size(); i++) {
            if (t.isAncestor(lca, i)) {
                if (t.isAncestor(i, u) || t.isAncestor(i, v)) {
                    src.push_back(i);
                }
            }
        }
    }
    for (int i: src) {
        hasVisited[i] = true;
        pq.push({0, i});
    }
    //cout << endl;
    while(!pq.empty()){
        int curNode = pq.front().second;
        int curDist = pq.front().first;
        hasVisited[curNode] = true;
        pq.pop();
        for(int i: adj[curNode]){
            if(hasVisited[i]) continue;
            hasVisited[i] = true;
            pq.push(make_pair(curDist + 1, i));
        }
        if(pq.empty()){
            return make_pair(curDist,curNode);
        }
    }
    return make_pair(-1,-1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    graph g;
    g.adj.resize(n), adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
        g.adj[u].push_back({1, v}), g.adj[v].push_back({1, u});
    }
    t.adj = adj;
    t.read(0);
    pair<int,int> p1 = BFS({0});
    pair<int,int> p2 = BFS({p1.second});
    pair<int,int> p3 = BFS({p2.second, p1.second});
    vector<int> v1 = g.dijk(p1.second);
    vector<int> v2 = g.dijk(p2.second);
    if (v1[p2.second] == n - 1) {
        int i;
        for (i = 0; i < n; i++) {
            if (i != p1.second && i != p2.second) {
                break;
            }
        }
        cout << n - 1 << '\n';
        cout << p1.second + 1 << " " << p2.second + 1 << " " << i + 1 << '\n';
        return 0;
    }
    cout << (v1[p3.second] + v2[p3.second] + v2[p1.second])/2 << '\n';
    cout << p1.second + 1 << " " << p2.second + 1 << " " << p3.second + 1 << '\n';

}
