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

template<class T>
struct Seg { // comb(ID,b) = b
    const T ID = 0;
    int n;
    vector<T> seg;

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }

    void pull(int p) { seg[p] = (seg[2 * p] + seg[2 * p + 1]); }

    void upd(int p, T val) { // set val at position p
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }

    T query(int l, int r) {    // min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = ra + seg[l++];
            if (r & 1) rb = seg[--r] + rb;
        }
        return ra + rb;
    }
};

struct BIT {
    vector<int> bit; //1-indexed
    void update_point(int ind, int val) {
        ind++;
        while (ind < bit.size()) {
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }

    void update_range(int l, int r, int x) {
        update_point(l, x);
        update_point(r + 1, -x);
    }

    int query(int b) {
        b++;
        int sum = 0;
        for (; b; b -= b & (-b)) {
            sum += bit[b];
        }
        return sum;
    }

    void construct(int N) {
        bit.resize(N + 1);
        for (int i = 0; i <= N; i++) {
            bit[i] = 0;
        }
    }
};

class Tree {
private: 
    int cntr = 0;
public:
    vector<vector<int>> adj;
    vector<int> st, en;
    void update(int n) {
        adj.resize(n);
        st.resize(n), en.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs(int curNode, int prevNode) {
        st[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
        en[curNode] = cntr++;
    }
};

class Solver {
public:
    Tree t;
    Seg<int> st;
    BIT stp; // range update point get
    int cur = 0;
    vector<int> replace;

    void update(int n, Tree &myTree) {
        st.init(2 * n + 2);
        stp.construct(2 * n + 2);
        replace.assign(n, -1);
        this->t = myTree;
    }

private:
    void add_node(int curNode) {
        stp.update_range(t.st[curNode], t.en[curNode], curNode + 1);
        st.upd(t.st[curNode], 1);
        cur++;
    }

    void remove_node(int curNode) {
        if (st.query(t.st[curNode], t.st[curNode]) == 0) {
            return;
        }
        stp.update_range(t.st[curNode], t.en[curNode], -curNode - 1);
        st.upd(t.st[curNode], 0);
        cur--;
    }

public:
    void try_add_node(int curNode) {
        if (st.query(t.st[curNode], t.en[curNode]) != 0) {
            return;
        }
        int x = (int) stp.query(t.st[curNode]);
        if (x != 0) {
            replace[curNode] = x - 1;
            remove_node(x - 1);
            add_node(curNode);
            return;
        }
        add_node(curNode);
    }

    void try_remove_node(int curNode) {
        remove_node(curNode);
    }
};

struct reporter {
    int myMax = 0;
    Solver s;
    Tree t1;

    void dfst1(int curNode, int prevNode) {
        s.try_add_node(curNode);
        myMax = max(myMax, s.cur);
        for (int i: t1.adj[curNode]) {
            if (i != prevNode) {
                dfst1(i, curNode);
            }
        }
        s.try_remove_node(curNode);
        if (s.replace[curNode] != -1) {
            s.try_add_node(s.replace[curNode]);
        }
        myMax = max(myMax, s.cur);
    }

    void solve() {
        int N;
        cin >> N;
        Tree t2;
        t1.update(N), t2.update(N);
        vector<int> p1(N), p2(N);
        for (int i = 1; i < N; i++) {
            int u;
            cin >> u;
            u--;
            p1[i] = u;
            t1.add_edge(u, i);
        }
        for (int i = 1; i < N; i++) {
            int u;
            cin >> u;
            u--;
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
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        reporter r;
        r.solve();
    }
}
