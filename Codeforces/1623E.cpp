#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>
#include <random>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

typedef int32_t ll;

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
struct segmentTree {
    vector<ll> vec;
    vector<ll> addLater;

    void push(int v) {
        addLater[2 * v + 1] = max(addLater[2 * v + 1], addLater[v]);
        addLater[2 * v + 0] = max(addLater[2 * v + 0], addLater[v]);
        vec[2 * v + 1] = max(vec[2 * v + 1], addLater[v]);
        vec[2 * v] = max(vec[2 * v], addLater[v]);
        addLater[v] = 0;
    }

    const ll INF = 1e18;

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return 0;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] = max(addLater[dum], val);
            return (vec[dum] = max(vec[dum], val));
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        ll left = upd(2 * dum, tl, mid, l, r, val);
        ll right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = max(vec[2 * dum], vec[2 * dum + 1]));
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
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};
struct Tree {
    vector<vector<int>> adj;
    vector<int> euler, st, en;
    segmentTreePoint seg;
    vector<int> depth;
    int dep = 0;
    int max_dep = 0;
    void dfs (int curNode, int prevNode) {
        euler.push_back(curNode);
        dep++;
        max_dep = max(max_dep, dep);
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
        euler.push_back(curNode);
        dep--;
    }
    void upd (int x) {
        seg.upd(st[x], en[x], 1);
    }
    int query (int x) {
        return seg.get(en[x]);
    }
    void read() {
        int n = adj.size();
        dfs (0, -1);
        st.assign(n, -1);
        en.assign(n, -1);
        seg.resz(euler.size());
        for (int i = 0; i < euler.size(); i++) {
            if (st[euler[i]] == -1)  {
                st[euler[i]] = i;
            } else {
                en[euler[i]] = i;
            }
        }
        depth.assign(n, -1);
        queue<pair<int,int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            int curNode = q.front().first;
            int curDist = q.front().second;
            q.pop();
            if (depth[curNode] != -1) {
                continue;
            }
            depth[curNode] = curDist;
            for (int i: adj[curNode]) {
                q.push({i, curDist + 1});
            }
        }
    }
};
vector<int> order;
int l[(int)2e5], r[(int)2e5], nxt[(int)2e5], rev_order[(int)2e5], parent[(int)2e5];
int dp[(int)2e5][20];

void process (int curNode) {
    if (curNode == -1) {
        return;
    }
    process(l[curNode]);
    order.push_back(curNode);
    process(r[curNode]);
}

int endUp (int curNode, int jump) {
    if (jump == 0) {
        return curNode;
    }
    int lg2 = log2(jump);
    return dp[endUp(curNode, jump - (1 << lg2))][lg2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    st.resz(14);
    int N, K;
    cin >> N >> K;
    segmentTree seg_path;
    seg_path.resz(2 * N);
    string s;
    cin >> s;
    Tree t;
    t.adj.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
        if (l[i] > 0) {
            parent[l[i]] = i;
        }
        if (r[i] > 0) {
            parent[r[i]] = i;
        }
        if (l[i] != -1) {
            t.adj[i].push_back(l[i]), t.adj[l[i]].push_back(i);
        }
        if (r[i] != -1) {
            t.adj[i].push_back(r[i]), t.adj[r[i]].push_back(i);
        }
    }
    t.read();
    process(0);
    for (int i = 0; i < order.size(); i++) {
        rev_order[order[i]] = i;
    }
    int prev = order.back();
    nxt[prev] = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[order[i]] == s[prev]) {
            nxt[order[i]] = nxt[prev];
        } else {
            nxt[order[i]] = prev;
            prev = order[i];
        }
    }
    for (int i = 0; i < N; i++) {
        dp[i][0] = parent[i];
        if (parent[i] == -1) {
            dp[i][0] = 0;
        }
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < N; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    vector<bool> bad;
    bad.assign(N, false);
    for (int i = 0; i < N; i++) {
        int cur = order[i];
        if (nxt[cur] == -1 || s[nxt[cur]] < s[cur]) {
            bad[cur] = true;
        }
    }
    vector<bool> taken;
    taken.assign(N, false);
    taken[0] = true;
    int cnt = 1;
    seg_path.upd(t.st[0], t.en[0], t.depth[0]);
    for (int i = 0; i < N; i++) {
        int curNode = order[i];
        if (taken[curNode] || bad[curNode]) {
            if (bad[curNode]) {
                t.upd(curNode);
            }
            continue;
        }
        int max_depth = seg_path.get(t.st[curNode], t.st[curNode]);
        int l = t.depth[curNode] - max_depth;
        //cout << curNode + 1 << " " << t.depth[curNode] << " " << max_depth << endl;
        if (t.query(parent[curNode]) != t.query(endUp(curNode, l))) {
            continue;
        }
        if (cnt + l <= K) {
            int cur = curNode;
            while (!taken[cur]) {
                seg_path.upd(t.st[cur], t.en[cur], t.depth[cur]);
                taken[cur] = true;
                cur = parent[cur];
                cnt++;
            }
        }
    }
    string str = "";
    string str1 = "";
    for (int i = 0; i < N; i++) {
        str += s[order[i]];
        str1 += s[order[i]];
        if (taken[order[i]]) {
            str += s[order[i]];
        }
    }
    cout << min(str, str1);


}
