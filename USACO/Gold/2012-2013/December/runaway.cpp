#include <bits/stdc++.h>
using namespace std;
template<class T>
class SegmentTree {
public:

    SegmentTree() {

    }

    void resz (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};

struct Query {
    int l, r, ind, res;
    int64_t k;
};

bool compIndex (Query q1, Query q2) {
    return (q1.ind < q2.ind);
}

bool compValue (Query q1, Query q2) {
    return (q1.k > q2.k);
}

class Queries {
    vector<int64_t> v;
    SegmentTree<int> st;
public:
    Queries (vector<int64_t> v) {
        this->v = v;
        st.resz(v.size());
    }

    void respond (vector<Query> &queries) {
        sort(queries.begin(), queries.end(), compValue);
        vector<pair<int,int> > tot;
        for (int i = 0; i < v.size(); i++) {
            tot.push_back(make_pair(v[i], i));
        }
        sort(tot.begin(), tot.end()), reverse(tot.begin(), tot.end());
        int prev = -1;
        vector< pair<int,int> > ans;
        for (auto& q: queries) {
            while (prev + 1 < v.size() && tot[prev + 1].first > q.k) {
                st.update(tot[++prev].second, 1);
            }
            q.res = st.query(q.l, q.r);
        }
        sort(queries.begin(), queries.end(), compIndex);
    }
};

class Tree {
public:
    vector<vector<int> > adj;
    vector<int> pre, post;
    vector<int64_t> depth;
    map<pair<int,int>, int64_t > myMap;
    int cntr = 0;
    
    void add_edge (int u, int v, int64_t w) {
        myMap[make_pair(u, v)] = myMap[make_pair(v, u)] = w;
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs (int curNode, int prevNode) {
        if (prevNode == -1) {
            depth[curNode] = 0;
        } else {
            depth[curNode] = depth[prevNode] + myMap[make_pair(curNode, prevNode)];
        }
        pre[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
        post[curNode] = cntr++;
    }

    Tree (int n) {
        adj.resize(n), pre.resize(n), post.resize(n), depth.resize(n);
    }

    void read (int64_t L) {
        int n = adj.size();
        dfs (0, -1);
        vector<int64_t> v(2 * n);
        for (int i = 0; i < adj.size(); i++) {
            v[pre[i]] = depth[i], v[post[i]] = depth[i];
        }
        Queries queries(v);
        vector<Query> vec(n);
        for (int i = 0; i < n; i++) {
            vec[i].l = pre[i], vec[i].r = post[i], vec[i].ind = i;
            vec[i].k = L + depth[i];
        }
        queries.respond(vec);
        for (auto& v: vec) {
            cout << (v.r - v.l + 1 - v.res)/2 << '\n';
        } 
    }
};

int main() {
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; 
    int64_t l;
    cin >> n >> l;
    Tree myTree(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        myTree.add_edge(i, x, y);
    }
    myTree.read(l);
}
