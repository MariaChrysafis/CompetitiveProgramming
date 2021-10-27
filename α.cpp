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
    return (x % MOD * y % MOD) % MOD;
}
ll add (ll x, ll y) {
    return (x % MOD + y % MOD) % MOD;
}
long long binPow (long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
long long inv (long long x) {
    return binPow(x, MOD - 2);
}
struct Graph {
    vector<vector<pair<int,int>>> adj; //node, distance
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
                assert(distance > d[val]);
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
        int n = adj.size();
        dist.resize(n);
        for (int i = 0; i < n; i++) {
            dist[i] = bfs(i);
        }
    }
};
long long fact (long long x) {
    if (x == 0) return 1;
    return (fact(x - 1) * x) % MOD;
}
vector<Tree> vec;
int main() {
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);
    ll N, M, X, Y;
    cin >> N >> M >> X >> Y;
    Graph g;
    g.adj.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g.adj[u].push_back({v, w});
        g.adj[v].push_back({u, w});
    }
    g.read();
    map<int,int> component;
    map<int,int> new_node;
    for (int i= 0; i < g.components.size(); i++) {
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
    for (int i = 0; i < vec.size(); i++) {
        vec[i].read();
    }
    ll c2 = 1;
    for (int i = 0; i < vec.size(); i++) {
        c2 = mult(mult(c2, mult(vec[i].dist.size(), vec[i].dist.size() - 1)), inv(2));
    }
    //--------------------------------VERIFFIED------------------
    ll sum[vec.size()];
    sum[0] = 0;
    ll prev[Y + 1];
    ll cur[Y + 1];
    for (int i = 0; i <= Y; i++) prev[i] = cur[i] = 0;
    for (int j = 0; j < vec[0].dist.size(); j++) {
        for (int k = j + 1; k < vec[0].dist.size(); k++) {
            if(vec[0].dist[j][k] <= Y) {
                prev[vec[0].dist[j][k]]++;
            }
            sum[0] = add(sum[0], vec[0].dist[j][k]);
        }
    }
    for (int i = 1; i < vec.size(); i++) {
        for (int y = 0; y <= Y; y++) {
            cur[y] = 0;
            sum[i] = 0;
            for (int j = 0; j < vec[i].dist.size(); j++) {
                for (int k = j + 1; k < vec[i].dist.size(); k++) {
                    long long distance = vec[i].dist[j][k];
                    if (y - distance >= 0) {
                        cur[y] = add(cur[y], prev[y - distance]);
                    }
                    sum[i] = add(sum[i], distance);
                }
            }
        }
        for (int y = 0; y <= Y; y++) {
            prev[y] = cur[y];
        }
    }
    ll ans = 0;
    for (int y = 0; y < Y - X * (int)vec.size(); y++) {
        ans = add(ans, mult(cur[y], add(y, mult(X, vec.size()))));
        ans %= MOD;
    }
    ll tot = 0;
    for (int i = 0; i < vec.size(); i++) {
        ll ch2 = (((ll)vec[i].dist.size() - 1) * (ll)vec[i].dist.size())/2;
        tot = add(tot, mult(sum[i], mult(c2, inv(ch2))));
    }
    ans = (tot + (c2 * X * (ll)vec.size()) % MOD - ans + MOD) % MOD * binPow(2, vec.size() - 1);
    ans %= MOD;
    ans *= fact(vec.size() - 1) % MOD;
    ans %= MOD;
    cout << ans << endl;
}
