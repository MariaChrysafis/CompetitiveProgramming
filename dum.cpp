#include <bits/stdc++.h>

using namespace std;

template<class T> struct Seg { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return a+b; }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] += val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// sum on interval [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};

class Tree {
    public:
    vector <vector<int> > w, new_adj, dp;
    vector<bool> t;
    vector<int> pre, post;
    vector <vector<int> > st, en;
    vector <pair<int, int> > edges;
    int cntr = 0;

    void dfs1(int curNode, int prevNode) {
        t[curNode] = true;
        dp[curNode][0] = prevNode;
        if (prevNode == -1) dp[curNode][0] = curNode;
        for (int i: w[curNode]) {
            if (i == prevNode) continue;
            if (!t[i]) {
                new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
                dfs1(i, curNode);
            } else {
                edges.push_back(make_pair(i, curNode));
            }
        }
    }

    void dfs2(int curNode, int prevNode) {
        pre[curNode] = cntr++;
        for (int i: new_adj[curNode]) {
            if (i != prevNode) {
                dfs2(i, curNode);
            }
        }
        post[curNode] = cntr++;
    }

    bool isAncestor(int u, int v) {
        return (pre[u] <= pre[v] && post[u] >= post[v]);
    }

    int goUp(int u, int v) {
        //assert(isAncestor(u, v));
        for (int i = (int) dp[0].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[v][i], u)) {
                v = dp[v][i];
            }
        }
        return v;
    }

    int leastCommonAncestor(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = dp[0].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[a][i], b)) {
                a = dp[a][i];
            }
        }
        return dp[a][0];
    }

    map <pair<int, pair < int, int> >, bool>
    myMap;

    void dfs(int curNode, int prevNode, Seg<int> &seg) {
        if (prevNode != -1) {
            for (int i: st[prevNode]) {
                seg.upd(pre[i], 1);
            }
        }
        for (int i: new_adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode, seg);
            }
        }

        if (prevNode != -1) {
            for (int i: w[curNode]) {
                for (int j: w[curNode]) {
                    if (!onPath(i, j, curNode)) {
                        myMap[make_pair(curNode, make_pair(i, j))] = true;
                        continue;
                    }
                    bool fine = true;
                    if (isAncestor(curNode, i)) {
                        int a = goUp(curNode, i);
                        fine = fine & (bool) (seg.query(pre[a], post[a]));
                    }
                    if (isAncestor(curNode, j)) {
                        int a = goUp(curNode, j);
                        fine = fine & (bool) (seg.query(pre[a], post[a]));
                    }
                    myMap[make_pair(curNode, make_pair(i, j))] = fine;
                }
            }
        } else {
            for (int i: w[curNode]) {
                for (int j: w[curNode]) {
                    if (i == j) continue;
                    if (!onPath(i, j, curNode)) myMap[make_pair(curNode, make_pair (i, j))] = false;
                    myMap[make_pair(curNode,make_pair(i, j))] = goUp(curNode, i) == goUp(curNode, j);
                }
            }
        }
        if (prevNode != -1) {
            for (int i: st[prevNode]) {
                seg.upd(pre[i], -1);
            }
        }
    }

    bool onPath(int a, int b, int c) {
        if (a == c || b == c) return true;
        if (isAncestor(a, b) || isAncestor(b, a)) {
            if (isAncestor(c, a) && isAncestor(b, c)) return true;
            if (isAncestor(c, b) && isAncestor(a, c)) return true;
            if (isAncestor(c, b) && isAncestor(c, a)) return false;
            if (isAncestor(b, c) && isAncestor(a, c)) return false;
            return false;
        }
        int l = leastCommonAncestor(a, b);
        return onPath(a, l, c) || onPath(b, l, c);
    }

    void init(int n, int m, vector<pair<int,int> > edges, int strt) {
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(22);
        }
        w.resize(n), new_adj.resize(n), t.assign(n, false), pre.resize(n), post.resize(n), st.resize(
                n), en.resize(n);
        for (auto& p: edges) {
            w[p.first].push_back(p.second), w[p.second].push_back(p.first);
        }
        dfs1(strt, -1);
        dfs2(strt, -1);
        for (auto &p: edges) {
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
        Seg<int> seg;
        seg.init(2 * n + 1);
        dfs(strt, -1, seg);
    }
};

struct State {
    pair<int,int> me;
    pair<int,int> box;
    bool operator < (const State& s1) const {
        if (s1.me != me) return (s1.me < me);
        return (s1.box < box);
    }
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    string grid[n];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    vector<pair<int,int> > edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vector<int> pos;
            for (int dx = -1; dx <= 1; dx++) {
                if (dx + i < 0 || dx + i == n) continue;
                for (int dy = -1; dy <= 1; dy++) {
                    if (dy + j < 0 || dy + j == m) continue;
                    if (abs(dx) + abs(dy) == 1 && grid[i][j] != '#' && grid[i + dx][j + dy] != '#') {
                        edges.push_back(make_pair(m * i + j, m * (i + dx) + j + dy));
                        pos.push_back(edges.back().second);
                    }
                }
            }
        }
    }
    State cur;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') cur.me = make_pair(i, j);
            else if (grid[i][j] == 'B') cur.box = make_pair(i, j);
        }
    }
    Tree myTree;
    myTree.init(n * m, edges.size(), edges, m * cur.me.first + cur.me.second);
    queue<pair<int,int> > dum;
    dum.push(cur.me);
    set<pair<int,int> > s;
    queue<State> myQueue;
    while (!dum.empty()) {
        pair<int,int> p = dum.front();
        dum.pop();
        if (s.count(p)) continue;
        s.insert(p);
        if (abs(p.first - cur.box.first) + abs(p.second - cur.box.second) == 1) {
            State myState; myState.me = p, myState.box = cur.box;
            myQueue.push(myState);
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && p.first + dx >= 0 && p.first + dx < n && p.second + dy >= 0 && p.second + dy < m && grid[p.first + dx][p.second + dy] == '.') {
                    if (!s.count(make_pair(p.first + dx, p.second + dy)))
                    dum.push(make_pair(p.first + dx, p.second + dy));
                }
            }
        }
    }
    set<State> vis;
    set<int> pos;
    while (!myQueue.empty()) {
        State myState = myQueue.front();
        myQueue.pop();
        if (vis.count(myState)) continue;
        vis.insert(myState);
        pos.insert(m * myState.box.first + myState.box.second);
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy ++) {
                if (myState.box.first + dx == myState.me.first && myState.box.second + dy == myState.me.second) {
                    continue;
                }
                if (abs(dx) + abs(dy) != 1) continue;
                pair<int,int> new_me = make_pair(myState.box.first + dx, myState.box.second + dy);
                if (new_me.first < 0 || new_me.second < 0 || new_me.first == n || new_me.second == m || grid[new_me.first][new_me.second] == '#') continue;
                if (!myTree.myMap[make_pair(myState.box.first * m + myState.box.second, make_pair(myState.me.first * m + myState.me.second, new_me.first * m +new_me.second))]) continue;
                State nxt;
                nxt.box = myState.box;
                nxt.me = new_me;
                myQueue.push(nxt);
            }
        }
        pair<int,int> nxt = make_pair(2 * myState.box.first - myState.me.first, 2 * myState.box.second - myState.me.second);
        if (nxt.first < 0 || nxt.first == n) continue;
        if (nxt.second < 0 || nxt.second == m) continue;
        if (grid[nxt.first][nxt.second] == '#') continue;
        myState.me = myState.box;
        myState.box = nxt;
        myQueue.push(myState);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (pos.count(m * u + v)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

}
