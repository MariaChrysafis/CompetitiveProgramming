#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#define ll int

using namespace std;
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return query(dum, tl, mid, l, r) + query(dum + 1, mid + 1, tr, l, r);
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = query(curX, x - 1) +  query(x + 1, curY) + y;
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
struct Tree {
    vector<vector<int>> adj;
    vector<int> strt, en, euler;
    int timer = 0;
    void dfs (int curNode, int prevNode) {
        strt[curNode] = timer++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
        en[curNode] = timer++;
    }
    void resz() {
        strt.resize(adj.size());
        en.resize(adj.size());
        dfs(0, -1);
        euler.resize(adj.size() * 2);
        for (int i = 0; i < strt.size(); i++) {
            euler[strt[i]] = i + 1;
            euler[en[i]] = i + 1;
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    Tree t;
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        u--;
        adj[u].push_back(i), adj[i].push_back(u);
    }
    t.adj = adj;
    t.resz();
    segmentTree st;
    st.resz(2 * n + 3);
    int ans[n];
    for (int i = v.size() - 1; i >= 0; i--) {
        st.update(t.strt[v[i].second], 1);
        //st.update(t.en[v[i].second], 1);
        //cout << t.strt[v[i].second] + 1 << " " << t.en[v[i].second] - 1 << endl;
        int x = st.query(t.strt[v[i].second] + 1, t.en[v[i].second] - 1);
        ans[v[i].second] = x;
    }
    for (int i = 0; i < n; i++){
        cout << ans[i] << endl;
    }

}
