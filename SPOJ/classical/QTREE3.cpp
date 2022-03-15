#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
const int MOD = 1e9;

template<class T>
struct Seg {
    const T ID = 0;

    T comb(T a, T b) { return max(a, b); }

    int n;
    vector<T> seg;

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }

    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }

    void upd(int p, T val) {
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }

    T query(int l, int r) {
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};

class HeavyLightDecomposition {
public:
    vector<vector<int>> adj;
    vector<int> sub;
    vector<int> id, inv_id;
    vector<int> topchain;
    vector<int> depth;
    vector<int> parent;
    Seg<int64_t> st;
    int cntr = 0;

    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void rec(int curNode, int prevNode) {
        parent[curNode] = prevNode;
        if (prevNode != -1) {
            depth[curNode] = depth[prevNode] + 1;
        } else {
            depth[curNode] = 0;
        }
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                rec(i, curNode);
                sub[curNode] += sub[i];
            }
        }
    }

    HeavyLightDecomposition(int n) {
        adj.resize(n);
        sub.resize(n);
        id.resize(n);
        topchain.assign(n, -1);
        parent.resize(n);
        st.init(n + 1);
    }

    void dfs(int curNode, int prevNode) {
        id[curNode] = cntr++;
        vector<pair<int, int>> vec;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                vec.push_back({sub[i], i});
            }
        }
        if (!vec.empty()) {
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
            topchain[vec[0].second] = topchain[curNode];
            for (int i = 1; i < vec.size(); i++) {
                topchain[vec[i].second] = vec[i].second;
            }
            for (auto &p: vec) {
                dfs(p.second, curNode);
            }
        }
    }

    int f (int a) {
        int val = INT_MAX;
        if (a == -1) {
            return val;
        }
        if (st.query(id[topchain[a]], id[a])) {
            int l = id[topchain[a]];
            int r = id[a];
            while (l != r) {
                int m = (l + r)/2;
                if (st.query(l, m)) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            val = min(val, l);
        }
        if (a != topchain[a]) {
            return min(f(topchain[a]), val);
        } else {
            return min(f(parent[a]), val);
        }
    }

    void upd(int ind, int x) {
        st.upd(id[ind], x);
    }

    void read(vector<int> arr) {
        depth.resize(adj.size());
        inv_id.resize(adj.size());
        rec(0, -1); //fill in all of the subtrees
        topchain[0] = 0;
        cntr = 0;
        dfs(0, -1); //fill in all of the ids and stuff
        for (int i = 0; i < arr.size(); i++) {
            upd(i, arr[i]);
        }
        for (int i = 0; i < adj.size(); i++) {
            inv_id[id[i]] = i;
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> vec;
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(--u, --v);
    }
    vector<int> arr;
    arr.resize(N);
    hld.read(arr);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int s;
            cin >> s;
            s--;
            if (hld.st.query(hld.id[s], hld.id[s]) == 0) {
                hld.st.upd(hld.id[s], 1);
            } else {
                hld.st.upd(hld.id[s], 0);
            }
        } else {
            int v;
            cin >> v;
            v--;
            int x = hld.f(v);
            if (x == INT_MAX) {
                cout << "-1\n";
                continue;
            }
            cout << hld.inv_id[x] + 1 << '\n';
        }
    }
}
