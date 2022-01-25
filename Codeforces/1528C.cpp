#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef int ll;
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a + b; }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};


struct segmentTreePoint {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }

};

class Tree {
public:
    vector<vector<int>> adj;
    vector<int> st, en;
    vector<int> euler;
    int cntr = 0;
public:
    Tree () {

    }
    void update (int n) {
        adj.resize(n);
        st.resize(n), en.resize(n);
    }
    Tree (int n) {
        update(n);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs (int curNode, int prevNode) {
        st[curNode] = cntr++;
        euler.push_back(curNode);
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        euler.push_back(curNode);
        en[curNode] = cntr++;
    }
};

class Solver {
public:
    Tree t;
    Seg<int> st;
    segmentTreePoint stp; // range update point get
    int cur = 0;
    vector<int> replace;

    Solver() {

    }

    void update (int n, Tree myTree) {
        st.init(2 * n + 2);
        stp.resz(2 * n + 2);
        replace.assign(n, -1);
        this->t = myTree;
    }

    Solver (int n, Tree myTree) {
        update(n, myTree);
    }
private:
    void add_node (int curNode) {
        stp.upd(t.st[curNode], t.en[curNode], curNode + 1);
        st.upd(t.st[curNode], 1);
        cur++;
    }

    void remove_node (int curNode) {
        if (st.query(t.st[curNode], t.st[curNode]) == 0) {
            return;
        }
        stp.upd(t.st[curNode], t.en[curNode], -curNode - 1);
        st.upd(t.st[curNode], 0);
        cur--;
    }
public:
    void try_add_node (int curNode) {
        if (st.query(t.st[curNode], t.en[curNode]) != 0) {
            return;
        }
        int x = (int)stp.get(t.st[curNode]);
        if (x != 0) {
            replace[curNode] = x - 1;
            remove_node(x - 1);
            add_node(curNode);
            return;
        }
        add_node(curNode);
    }

    void try_remove_node (int curNode) {
        remove_node(curNode);
    }
};

struct reporter {
    int myMax = 0;
    Solver s;
    Tree t1;
    void dfst1 (int curNode, int prevNode) {
        s.try_add_node(curNode);
        myMax = max(myMax, s.cur);
        for (int i: t1.adj[curNode]) {
            if (i != prevNode) {
                dfst1 (i, curNode);
            }
        }
        s.try_remove_node(curNode);
        if (s.replace[curNode] != -1) {
            s.try_add_node(s.replace[curNode]);
        }
        myMax = max(myMax, s.cur);
    }
    void solve () {
        int N;
        cin >> N;
        Tree t2(N);
        t1.update(N);
        vector<int> p1(N), p2(N);
        for (int i = 1; i < N; i++) {
            int u; cin >> u; u--;
            p1[i] = u;
            t1.add_edge(u, i);
        }
        for (int i = 1; i < N; i++) {
            int u; cin >> u; u--;
            p2[i] = u;
            t2.add_edge(u, i);
        }
        t2.dfs(0, -1);
        s.update(N, t2);
        dfst1(0, -1);
        cout << myMax << '\n';
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); int t; cin >> t; while (t--) { reporter r; r.solve(); }
}
