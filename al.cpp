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
const ll MAX = 400001;
struct Query {
    ll l;
    ll r;
    ll k;
    ll index;
};

ll tree[1 << 18]; // BIT

void update_tree(ll pos) {
    while (pos <= MAX) {
        tree[pos] += 1;
        pos += (pos & -pos);
    }
}

ll query_tree(ll pos) {
    ll result = 0;

    while (pos > 0) {
        result += tree[pos];
        pos -= (pos & -pos);
    }

    return result;
}

struct Solver {
    ll n;
    ll q;
    vector<Query> queries;
    vector<pair<ll,ll>> arr;
    vector<ll> read() {
        for (ll i = 0; i < (1 << 18); i++) {
            tree[i] = 0;
        }
        sort(arr.rbegin(), arr.rend());
        vector<ll> result(q);
        sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) { return a.k > b.k; });
        ll pos = 0;
        for (ll i = 0; i < q; ++i) {
            while (pos < n && arr[pos].first > queries[i].k) {
                update_tree(arr[pos].second + 1);
                ++pos;
            }

            result[queries[i].index] = query_tree(queries[i].r) - query_tree(queries[i].l - 1);
        }

        return result;
    }
};
struct Tree{
    vector<vector<pair<ll,ll>>> adj;
    map<pair<int,int>,ll> myMap;
    vector<ll> first, last;
    vector<ll> dist;
    vector<ll> sub;
    vector<ll> parent;
    ll counter = 0;
    void pre_euler(){
        for (int i = 0; i < adj.size(); i++) {
            for (auto p: adj[i]) {
                myMap[{(int)p.first, (int)i}] = p.second;
            }
        }
        first.resize(adj.size());
        last.resize(adj.size());
        dist.assign(adj.size(), -1);
        sub.resize(adj.size());
        parent.resize(adj.size());
        subt(0, -1);
        dfs(0, -1);
        for (int i = 0; i < adj.size(); i++) {
            dist[i] = memoize(i);
        }
    }
    ll memoize (ll curNode) {
        if (dist[curNode] != -1) return dist[curNode];
        return (dist[curNode] = dist[parent[curNode]] + myMap[{curNode, parent[curNode]}]);
    }
    ll subt (ll curNode, ll prevNode) {
        parent[curNode] = prevNode;
        sub[curNode] = 1;
        for (pair<ll,ll> p: adj[curNode]) {
            if (p.first != prevNode) {
                sub[curNode] += subt(p.first, curNode);
            }
        }
        return sub[curNode];
    }
    void dfs(ll node, ll parent){
        first[node] = counter++;
        for(pair<ll,ll> p: adj[node]){
            if(p.first != parent){
                dfs(p.first, node);
            }
        }
        last[node] = counter++;
    }
};
int main() {
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    Tree t;
    ll n, l;
    cin >> n >> l;
    t.adj.resize(n);
    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        t.adj[i + 1].push_back({a, b});
        t.adj[a].push_back({i + 1, b});
    }
    t.pre_euler();
    vector<ll> euler(2 * n);
    for (ll i = 0; i < n; i++) {
        euler[t.first[i]] = t.dist[i];
        euler[t.last[i]] = t.dist[i];
    }
    Solver s;
    s.n = 2 * euler.size();
    s.arr.resize(s.n);
    for (ll i = 0; i < s.n; i++) {
        s.arr[i].first = euler[i];
        s.arr[i].second = i;
    }
    s.q = n;
    s.queries.resize(n);
    for (ll i = 0; i < n; i++) {
        s.queries[i].l = t.first[i];
        s.queries[i].r = t.last[i];
        s.queries[i].k = l + t.dist[i];
        s.queries[i].index = i;
    }
    vector<ll> v = s.read();
    for (ll i = 0; i < v.size(); i++) {
        cout << t.sub[i] - v[i]/2 << endl;
    }

}
