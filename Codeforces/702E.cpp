#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;
struct Node {
    ll s; //sum of weights
    ll m; //minimal weight amongst all nodes
};
vector<vector<Node>> dp;
vector<vector<int>> nxt;
ll powr (ll x) {
    if (x == 0) return 1;
    return powr(x - 1) * 2;
}
Node rec (int node, ll dist) {
    //cout << node << " " << dist << '\n';
    if (dist == 0) {
        return (Node){0, (int)1e9};
    }
    ll x = log2(dist);
    //cout << x << endl;
    Node n1 = dp[node][x];
    Node n2 = rec(nxt[node][x], dist - powr(x));
    Node ans;
    ans.s = n1.s + n2.s;
    ans.m = min(n1.m, n2.m);
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n; ll k; cin >> k;
    int out[n];
    for (int i = 0; i < n; i++) cin >> out[i];
    int weight[n];
    for (int i = 0; i < n; i++) cin >> weight[i];
    dp.resize(n), nxt.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(35);
        nxt[i].resize(35);
    }
    for (int i = 0; i < n; i++) {
        dp[i][0].s = dp[i][0].m = weight[i];
        nxt[i][0] = out[i];
    }
    for (int j = 1; j < dp[0].size(); j++) {
        for (int i = 0; i < n; i++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
    for (int j = 1; j < dp[0].size(); j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j].s = dp[i][j - 1].s + dp[nxt[i][j - 1]][j - 1].s;
            dp[i][j].m = min(dp[i][j - 1].m, dp[nxt[i][j - 1]][j - 1].m);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << rec(i, k).s << " " << rec(i, k).m << '\n';
    }
}
