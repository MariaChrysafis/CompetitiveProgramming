#include <bits/stdc++.h>
using namespace std;
template<class T>
class SegmentTree {
public:
 
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }
 
    void update (int x, T y) {
        x += N - 1;
        val[x] += y;
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
vector<vector<int> > adj, new_adj, dp;
vector<bool> hasVisited;
vector<int> pre, post;
vector<vector<int> > st, en; 
vector<vector<pair<int,int> > > queries;
vector<pair<int,int > > edges;
//st[i] is which ones start at i
//en[i] is which ones end at i
int cntr = 0;
void dfs1 (int curNode, int prevNode) {
    hasVisited[curNode] = true;
    dp[curNode][0] = max(prevNode, 0);
    for (int i: adj[curNode]) {
        if (i == prevNode) continue;
        if (!hasVisited[i]) {
            new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
            dfs1 (i, curNode);
        } else {
            edges.push_back(make_pair(i, curNode));
        }
    }
}
void dfs2 (int curNode, int prevNode) {
    pre[curNode] = cntr++;
    for (int i: new_adj[curNode]) {
        if (i != prevNode) {
            dfs2 (i, curNode);
        }
    }
    post[curNode] = cntr++;
}
bool isAncestor (int u, int v) {
    //is u an ancestor of v?
    return (pre[u] <= pre[v] && post[u] >= post[v]);
}
 
int goUp (int u, int v) {
    assert(isAncestor(u, v));
    for (int i = (int)dp[0].size() - 1; i >= 0; i--)  {
        if (!isAncestor(dp[v][i], u)) {
            v = dp[v][i];
        }
    }
    return v;
}
 
int leastCommonAncestor (int a, int b) {
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;
    for (int i = dp[0].size() - 1; i >= 0; i--) {
        if (!isAncestor(dp[a][i], b)) {
            a = dp[a][i];
        }
    }
    return dp[a][0];
}
 
map<pair<int,pair<int,int> >, bool> myMap;
 
void dfs (int curNode, int prevNode, SegmentTree<int>& seg) {
    if (prevNode != -1) {
        for (int i: st[prevNode]) {
            //add in i
            seg.update(pre[i], 1);
        }
    }
    for (int i: new_adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode, seg);
        }
    }
    
    if (curNode != 0) { 
        for (auto& p: queries[curNode]) {
            bool fine = true;
            if (isAncestor(curNode, p.first)) {
                int a = goUp(curNode, p.first);
                fine = fine & (bool)(seg.query(pre[a], post[a]));
            }
            if (isAncestor(curNode, p.second)) {
                int a = goUp(curNode, p.second);
                fine = fine & (bool)(seg.query(pre[a], post[a]));
            }
            myMap[make_pair(curNode, p)] = fine;
        }
    } else {
        for (auto& p: queries[curNode]) {
            myMap[make_pair(curNode, p)] = goUp(curNode, p.first) == goUp(curNode, p.second);
        }
    }
    if (prevNode != -1) {
        for (int i: st[prevNode]) {
            //remove i
            seg.update(pre[i], -1);
        }
    }
}
 
bool onPath (int a, int b, int c) {
    //cout << a + 1 << " " << b + 1 << " " << c + 1 << '\n';
    if (a == c || b == c) return true;
    if (isAncestor(a, b) || isAncestor(b, a)) {
    if (isAncestor(c, a) && isAncestor(b, c)) return true;
    if (isAncestor(c, b) && isAncestor(a, c)) return true;
    if (isAncestor(c, b) && isAncestor(c, a)) return false;
    if (isAncestor(b, c) && isAncestor(a, c)) return false;
    return false;
    }
    int l = leastCommonAncestor(a, b);
    assert(isAncestor(l, a) && isAncestor(l, b));
    return onPath(a, l, c) || onPath(b, l, c);
}
 
int main () {
    int n, m, q;
    cin >> n >> m >> q;
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(32);
    }
    adj.resize(n), new_adj.resize(n), hasVisited.assign(n, false), pre.resize(n), post.resize(n), st.resize(n), en.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    for (auto& p: edges) {
        int u = p.first, v = p.second;
        if (!isAncestor(u, v)) {
            swap(u, v);
        }
        st[u].push_back(v);
        en[v].push_back(u);
    }
    for (int j = 1; j < dp[0].size(); j++) {
        for (int i = 0; i < dp.size(); i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    SegmentTree<int> seg(2 * n);
    vector<pair<int,pair<int,int> > > vec;
    queries.resize(n);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        if (!onPath(a, b, c)) {
            myMap[make_pair(c, make_pair(a, b))] = true;
        } else if (b == c || c == a) {
            myMap[make_pair(c, make_pair(a, b))] = false;
        } else {
            queries[c].push_back(make_pair(a, b));
        }
        vec.push_back(make_pair(c, make_pair(a, b)));
    }
    dfs(0, -1, seg);
    for (auto& p: vec) {
        assert(myMap.count(p));
        if (myMap[p]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
 
}
