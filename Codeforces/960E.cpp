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
typedef long long ll;
vector<ll> v;
const int MOD = 1e9 + 7;
void red (ll& x) {
    if (x > 0) {
        x %= MOD;
        return;
    }
    x = MOD - x;
    x %= MOD;
    x = MOD - x;
    x %= MOD;
}
struct Tree {
private:
    vector<vector<ll>> adj;
    vector<vector<ll>> depth;
    vector<ll> dist;
    vector<ll> sub;
    vector<ll> parent;
    ll ans = 0;
public:
    Tree (int n) {
        adj.resize(n);
        depth.assign(n, {0, 0});
        parent.resize(n);
        sub.resize(n);
        dist.resize(n);
    }
    void set_ans (ll res) {
        this->ans = res;
    }
    void add_edge (int x, int y) {
        adj[x].push_back(y), adj[y].push_back(x);
    }
    void dfs (int curNode, int prevNode, int d) {
        parent[curNode] = prevNode;
        depth[curNode][0] = 0;
        depth[curNode][1] = 0;
        depth[curNode][d % 2]++;
        dist[curNode] = d;
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode, d + 1);
                depth[curNode][0] += depth[i][0];
                depth[curNode][1] += depth[i][1];
                sub[curNode] += sub[i];
            }
        }
    }
    int read() {
        dfs(0, -1, 0);
        for (int i = 0; i < adj.size(); i++) {
            vector<int> children;
            for (int j: adj[i]) {
                if (j != parent[i]) {
                    children.push_back(j);
                }
            }
            ll cnt = 0;
            for (int j: children) {
                cnt += (depth[j][dist[i] % 2] * (sub[i] - sub[j] - 1)) % MOD;
                cnt -= (depth[j][(dist[i] + 1) % 2] * (sub[i] - sub[j] - 1)) % MOD;
            }
            vector<ll> tot = {depth[0][0], depth[0][1]};
            cnt += (depth[i][dist[i] % 2] * (sub[0] - sub[i] + 1)) % MOD;
            cnt -= (depth[i][(dist[i] + 1) % 2] * (sub[0] - sub[i] + 1)) % MOD;
            cnt += ((tot[dist[i] % 2] - depth[i][dist[i] % 2] + 1) * sub[i]) % MOD;
            cnt -= ((tot[(dist[i] + 1) % 2] - depth[i][(dist[i] + 1) % 2]) * sub[i]) % MOD;
            red(cnt);
            ll val = (v[i] * cnt);
            red(val);
            ans += val;
            red(ans);
        }
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    v.resize(n);
    ll val = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        val -= v[i];
        red(val);
    }
    Tree t(n);
    t.set_ans(val);
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        t.add_edge(x - 1, y - 1);
    }
    cout << t.read();
}
