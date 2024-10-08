#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
ll mult (ll x, ll y) {
    return ((x % MOD) * (y % MOD)) % MOD;
}
ll add (ll x, ll y) {
    return ((x % MOD) + (y % MOD)) % MOD;
}
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
long long inv (long long x) {
    return binPow(x, MOD - 2);
}
struct Graph {
    vector<vector<pair<int,int>>> adj;
    vector<vector<int>> components;
    vector<bool> hasVisited;
    void dfs (int curNode) {
        if (hasVisited[curNode]) {
            return;
        }
        components.back().push_back(curNode), hasVisited[curNode] = true;
        for (auto p: adj[curNode]) {
            dfs(p.first);
        }
    }
    void read() {
        int n = adj.size();
        hasVisited.resize(n);
        for (int i = 0; i < n; i++) {
            hasVisited[i] = false;
        }
        for (int i = 0; i < n; i++) {
            if (!hasVisited[i]) {
                components.emplace_back(), dfs(i);
            }
        }
    }
};
struct Tree {
    vector<vector<pair<int,int>>> adj; //dist, val
    vector<vector<int>> dist;
    vector<int> bfs (int x) {
        priority_queue<pair<int,int>> pq; //-dist, val
        pq.push({0, x});
        vector<bool> hasVisited(adj.size());
        vector<int> d(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            hasVisited[i] = false;
            d[i] = 0;
        }
        while (!pq.empty()) {
            int distance = -pq.top().first;
            int val = pq.top().second;
            pq.pop();
            if (hasVisited[val]) {
                continue;
            }
            d[val] = distance;
            hasVisited[val] = true;
            for (auto p: adj[val]) {
                pq.push(make_pair(-p.first - distance, p.second));
            }
        }
        return d;
    }
    void read() {
        for (int i = 0; i < adj.size(); i++) {
            dist.push_back(bfs(i));
        }
    }
};
long long fact (long long x) {
    ll ans = 1;
    for (int i = 1; i <= x; i++) {
        ans = mult(ans, i);
    }
    return ans;
}
vector<Tree> vec;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;
    Graph g;
    g.adj.resize(N);
    for (int i = 0; i < M; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g.adj[u].push_back({v, w});
        g.adj[v].push_back({u, w});
    }
    g.read();
    map<int,int> component;
    map<int,int> new_node;
    for (int i = 0; i < g.components.size(); i++) {
        for (int j = 0; j < g.components[i].size(); j++) {
            component[g.components[i][j]] = i;
            new_node[g.components[i][j]] = j;
        }
    }
    vec.resize(g.components.size());
    for (int i = 0; i < g.components.size(); i++) {
        vec[i].adj.resize(g.components[i].size());
    }
    for (int i = 0; i < g.adj.size(); i++) {
        for (auto p: g.adj[i]) {
            vec[component[i]].adj[new_node[i]].push_back({p.second, new_node[p.first]});
        }
    }
    ll sz = vec.size();
    assert(sz == N - M);
    ll c2 = 1;
    for (int i = 0; i < sz; i++) {
        vec[i].read();
        c2 = mult(mult(c2, mult(vec[i].dist.size(), (int)vec[i].dist.size() - 1)), inv(2));
    }
    ll sum[vec.size()];
    sum[0] = 0;
    ll prev[Y];
    ll cur[Y];
    for (int i = 0; i < Y; i++) {
        prev[i] = cur[i] = 0;
    }
    for (int j = 0; j < vec[0].dist.size(); j++) {
        for (int k = j + 1; k < vec[0].dist.size(); k++) {
            if(vec[0].dist[j][k] < Y) {
                prev[vec[0].dist[j][k]]++;
                prev[vec[0].dist[j][k]] %= MOD;
            }
            sum[0] = add(sum[0], vec[0].dist[j][k]);
        }
    }
    for (int i = 1; i < vec.size(); i++) {
        for (int y = 0; y < Y; y++) {
            cur[y] = sum[i] = 0;
            for (int j = 0; j < vec[i].dist.size(); j++) {
                for (int k = j + 1; k < vec[i].dist.size(); k++) {
                    ll distance = vec[i].dist[j][k];
                    if (y - distance >= 0) {
                        cur[y] = add(cur[y], prev[y - distance]);
                    }
                    sum[i] = add(sum[i], distance);
                }
            }
        }
        for (int y = 0; y < Y; y++) {
            prev[y] = cur[y];
        }
    }
    ll ans = 0;
    for (int y = 0; y < Y - X * sz; y++) {
        ans = add(ans, mult(prev[y], add(y, mult(X, (ll)vec.size()))));
    }
    ll tot = 0;
    for (int i = 0; i < sz; i++) {
        ll ch2 = mult(mult((ll)vec[i].dist.size() - 1, (ll)vec[i].dist.size()), inv(2));
        tot = add(tot, mult(sum[i], mult(c2, inv(ch2))));
    }
    ans = mult(add(add(tot, mult(c2, mult(X, (ll)vec.size()))), MOD - ans), binPow(2, sz - 1));
    ans = mult(ans, fact(sz - 1));
    cout << ans;
}
