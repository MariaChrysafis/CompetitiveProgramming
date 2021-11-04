#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
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
    ll INF = 1e16;
    ll weight[100000];
    ll mark[100000];
    ll parent[100000];
    vector <Pair> graph[100000];
    priority_queue <Pair> pq;

    ll mst() {
        for (ll i = 0; i <= n; i++) {
            weight[i] = INF;
            mark[i] = false;
        }
        weight[0] = 0;
        Pair p = {0, 0};
        parent[0] = -1;
        pq.push(p);
        ll counter = 0;
        while (!pq.empty()) {
            counter++;
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
                    parent[a] = x;
                    pq.push(pr);
                }
            }
        }
        ll cost = 0;
        for (int i = 0; i < n; i++) {
            cost += weight[i];
        }
        return cost;
    }
};
int main() {
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> v(n);
    Graph g;
    g.n = n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) {
                g.graph[j].push_back({i, -(v[i] ^ v[j])});
            }
        }
    }
    cout << -g.mst();
}
