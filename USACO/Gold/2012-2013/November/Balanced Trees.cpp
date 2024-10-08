#include <bits/stdc++.h>
using namespace std;
struct State {
    int min_depth;
    int cur_depth;
    int max_depth;
};
class Tree {
    vector<int> sgn, sub, parent;
    vector<vector<int> > adj;
    vector<bool> hasVisited;
    vector<State> up, down;
    int sz;
public:
    void upd_sgn (int x, int y) {
        sgn[x] = y;
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    Tree (int n) {
        sgn.resize(n), adj.resize(n), hasVisited.assign(n, false), sub.resize(n), parent.resize(n), up.resize(n), down.resize(n);
    }
    int dfs_sub (int curNode, int prevNode) {
        parent[curNode] = prevNode, sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i]) {
                sub[curNode] += dfs_sub(i, curNode);
            }
        }
        return (sz = sub[curNode]);
    }
    int find_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i] && sub[i] > sz/2) {
                return find_centroid(i, curNode);
            }
        }
        return curNode;
    }
    int ans = 0;
    map<pair<int,int> ,int> myMapUp, myMapDown;
    void upd (State s, map<pair<int,int>,int> &myMap)  {
        pair<int,int> key= make_pair(s.cur_depth, s.min_depth);
        myMap[key] = max(myMap[key], s.max_depth);
    }
    void add (int st) {
        queue<int> q;
        q.push(st);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            upd(up[x], myMapUp);
            upd(down[x], myMapDown);
            for (int i: adj[x]) {
                if (hasVisited[i] || i == parent[x]) {
                    continue;
                }
                q.push(i);
            }
        }
    }
    vector<int> update (int st) {
        vector<int> tot;
        queue<int> q;
        q.push(st);
        while (!q.empty()) {
            int x = q.front();
            tot.push_back(x);
            q.pop();
            up[x].cur_depth = down[x].cur_depth = up[parent[x]].cur_depth + sgn[x];
            up[x].min_depth = min(sgn[x] + min(0, up[parent[x]].min_depth), 0);
            up[x].max_depth = max(sgn[x] + max(0, up[parent[x]].max_depth), 0);
            down[x].min_depth = min(min(down[x].cur_depth, down[parent[x]].min_depth), 0);
            down[x].max_depth = max(max(down[x].cur_depth, down[parent[x]].max_depth), 0);
            if (up[x].cur_depth == 0 && up[x].min_depth == 0) {
                ans = max(ans, up[x].max_depth);
            }
            if (down[x].cur_depth == 0 && down[x].min_depth == 0) {
                ans = max(ans, down[x].max_depth);
            }
            for (int i: adj[x]) {
                if (i != parent[x] && !hasVisited[i]) {
                    q.push(i);
                }
            }
        }
        return tot;
    }
    void solve (int x) {
        myMapUp.clear(), myMapDown.clear();
        dfs_sub (x, -1);
        int centroid = find_centroid(x, -1); 
        dfs_sub (centroid, -1);
        hasVisited[centroid] = true;
        up[centroid].min_depth = min(sgn[centroid], 0);
        up[centroid].cur_depth = sgn[centroid];
        up[centroid].max_depth = max(sgn[centroid], 0);
        down[centroid] = up[centroid];
        int t = 2;
        while (t--) {
            myMapUp.clear(), myMapDown.clear();
            for (int dum: adj[centroid]) {
                if (hasVisited[dum]) {
                    continue;
                }
                for (int i: update(dum)) {
                    if (up[i].min_depth == 0 && myMapDown.count(make_pair(sgn[centroid] - up[i].cur_depth, sgn[centroid] - up[i].cur_depth))) {
                        ans = max(ans, max(up[i].cur_depth - sgn[centroid], 0) + myMapDown[make_pair(sgn[centroid] - up[i].cur_depth, sgn[centroid] - up[i].cur_depth)]);
                    }
                    ans = max(ans, myMapUp[make_pair(sgn[centroid] - down[i].cur_depth, 0)]);
                }
                add(dum);
            }
            reverse(adj[centroid].begin(), adj[centroid].end());
        }
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve(i);
            }
        }
    }
};
int main() {
    freopen("btree.in", "r", stdin);
    freopen("btree.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        x--;
        tree.add_edge(i, x);
    }
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        tree.upd_sgn(i, ((c == '(') ? 1 : -1));
    }
    tree.solve(0);
    cout << tree.ans << '\n';
}
