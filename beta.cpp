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
#define ll int
#include <map>

using namespace std;
struct segmentTree {
    vector<ll> vec;
    vector<ll> addLater;

    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const ll INF = 1e8;

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        ll left = upd(2 * dum, tl, mid, l, r, val);
        ll right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return min(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        addLater.assign(sz * 2, 0);
    }

};
struct Edge {
    int u, v, w;
};
struct Tree{
    vector<vector<int>> adj;
    vector<int> last, first;
    vector<int> euler;
    int counter = 0;
    void pre_euler(){
        euler.resize( 2 * adj.size()), first.resize(adj.size()), last.resize(adj.size());
        dfs(0, -1, 0);
        for (int i = 0; i < adj.size(); i++) {
            euler[first[i]] = i;
            euler[last[i]] = i;
        }
    }
    void dfs(int node, int parent, int h){
        first[node] = counter++;
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node, h + 1);
            }
        }
        last[node] = counter++;
    }
};
int main() {
    //freopen("snowcow.in", "r", stdin);
    //freopen("snowcow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    Tree t;
    t.adj.resize(N);
    vector<Edge> v1(N - 1);
    vector<vector<pair<int,int>>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        cin >> v1[i].u >> v1[i].v >> v1[i].w;
        v1[i].u--, v1[i].v--;
        t.adj[v1[i].u].push_back(v1[i].v);
        t.adj[v1[i].v].push_back(v1[i].u);
        adj[v1[i].u].push_back({v1[i].v, v1[i].w});
    }
    t.pre_euler();
    vector<Edge> v2(N - 1);
    int weight[N];
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        v2[i] = {u, v, w};
        weight[u] = w;
    }
    queue<int> q;
    int depth[N];
    bool hasVisited[N];
    for (int i = 0; i < N; i++) {
        depth[i] = 0;
        hasVisited[i] = false;
    }
    q.push(0);
    hasVisited[0] = true;
    weight[0] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto p: adj[x]) {
            if (!hasVisited[p.first]) {
                depth[p.first] = depth[x] + p.second;
                q.push(p.first);
                hasVisited[p.first] = true;
            }
        }
    }
    segmentTree st;
    segmentTree st1;
    st.resz(2 * N), st1.resz(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        st.upd(i, i, depth[t.euler[i]] + weight[t.euler[i]]);
        st1.upd(i, i, depth[t.euler[i]]);
    }
    for (int i = 0; i < 2 * N; i++) {
        cout << st.get(i, i) << " ";
    }
    cout << endl;
    for (int i = 0; i < 2 * N; i++) {
        cout << st1.get(i, i) << " ";
    }
    cout << endl;
    while(Q--) {
        int tc;
        cin >> tc;
        if (tc == 1) {
            int i; cin >> i;
            int w; cin >> w;
            i--;
            if (i >= N - 1) {
                i -= (N - 1);
                //update yellow edge
                int delta = w - v2[i].w;
                v2[i].w += delta;
                //cout << v2[i].u << " ? " << v2[i].v << " " << delta << endl;
                st.upd(t.first[v2[i].u], t.first[v2[i].u], delta);
                st.upd(t.last[v2[i].u], t.last[v2[i].u], delta);
            } else {
                //udpate white edge
                int delta = w - v1[i].w;
                v1[i].w += delta;
                st.upd(t.first[v1[i].v], t.last[v1[i].v], delta);
                st1.upd(t.first[v1[i].v], t.last[v1[i].v], delta);
            }
        } else {
            int u;
            cin >> u;
            int v;
            cin >> v;
            u--, v--;
            cout << st.get(t.first[u], t.last[u]) -st1.get(t.first[u], t.first[u]) + st1.get(t.first[v], t.first[v]) << endl;
        }
    }


}
