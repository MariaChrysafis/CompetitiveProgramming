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
struct segmentTree {
    vector<ll> vec;
    vector<ll> setLater;

    void push(int v) {
        if (setLater[v] == -1) {
            return;
        }
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = setLater[v];
        setLater[2 * v] = setLater[v];
        vec[2 * v] = setLater[v];
        setLater[v] = -1;
    }

    const ll INF = 0;

    void upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            vec[dum] = val;
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = max(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return max(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, -1);
    }
};
struct Graph {
    vector<vector<int>> adj;
    vector<int> st, en, parent;
    int cntr = 0;
    void dfs (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        st[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        en[curNode] = cntr++;
    }
    void read (int n) {
        adj.resize(n), st.resize(n), en.resize(n), parent.resize(n);
        dfs(0, -1);
    }
};
segmentTree st;
Graph g;
int state (int v) {
    if (st.get(g.st[v], g.en[v]) == 2) {
        return 0;
    }
    return st.get(g.st[v], g.st[v]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    g.adj.resize(n);
    st.resz(2 * n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back(v), g.adj[v].push_back(u);
    }
    g.read(n);
    int Q;
    cin >> Q;
    while (Q--) {
        int t;
        cin >> t;
        int v;
        cin >> v;
        v--;
        if (t == 1) {
            if (st.get(g.st[v], g.en[v]) == 2 && v != 0) {
                st.upd(g.st[g.parent[v]], g.st[g.parent[v]], 2);
            }
            st.upd(g.st[v], g.en[v], 1);
        } else if (t == 2) {
            st.upd(g.st[v], g.st[v], 2);
        } else {
            cout << state(v) << '\n';
        }
    }
}
