#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <climits>
#include <queue>
#include <set>
#define ll long long
using namespace std;
struct Pair {
    ll neighbor, weight;
};
bool operator<(Pair a, Pair b){
    return a.weight > b.weight;
}
struct Graph {
    ll n;
    ll INF = LLONG_MAX/2;
    ll weight[100001];
    ll mark[100001];
    vector <Pair> graph[100001];
    priority_queue <Pair> pq;
 
    ll mst() {
        for (ll i = 0; i < n; i++) {
            weight[i] = INF;
            mark[i] = false;
        }
        weight[0] = 0;
        Pair p = {0, 0};
        pq.push(p);
        while (!pq.empty()) {
            ll x = pq.top().neighbor;
            pq.pop();
            if (mark[x]) {
                continue;
            }
            mark[x] = true;
            for (Pair pr: graph[x]) {
                ll a = pr.neighbor;
                ll b = pr.weight;
                if (!mark[a] && weight[a] > b) {
                    weight[a] = b;
                    pq.push(pr);
                }
            }
        }
        ll cost = 0;
        for (int i = 0; i < n; i++) {
            cost += weight[i];
            if (weight[i] == INF) {
                return -1;
            }
        }
        return cost;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int m;
    cin >> m;
    Graph g;
    g.n = n;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g.graph[u].push_back({v, w});
        g.graph[v].push_back({u, w});
    }
    ll x = g.mst();
    if (x == -1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << x;
    }
}
