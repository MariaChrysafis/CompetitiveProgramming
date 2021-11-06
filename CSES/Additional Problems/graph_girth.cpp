#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
 
using namespace std;
const int INF = 1e8;
struct graph{
    vector<vector<int>> adj; //{-weight, node}
    int bfs (int src) {
        int ans = (int)1e9;
        queue<int> q;
        vector<int> dist;
        dist.assign(adj.size(), -1);
        q.push(src);
        dist[src] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i: adj[x]) {
                if (dist[i] >= dist[x]){
                    ans = min(ans, dist[i] + dist[x] + 1);
                }
                if (dist[i] == -1) {
                    dist[i] = dist[x] + 1;
                    q.push(i);
                }
            }
        }
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    graph g;
    int n, m;
    cin >> n >> m;
    g.adj.resize(n);
    vector<pair<int,int>> vec;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.adj[--u].push_back(--v);
        g.adj[v].push_back(u);
    }
    int ans = (int)1e9;
    for (int i = 0; i < n; i++) {
        ans = min(ans, g.bfs(i));
    }
    if (ans > n) {
        ans = -1;
    }
    cout << ans;
}
