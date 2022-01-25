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

const int MOD = 1e9 + 7;

ll mult(ll x, ll y) {
    x %= MOD, y %= MOD;
    return (x * y) % MOD;
}

ll binPow(ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}

ll inv(ll x) {
    return binPow(x, MOD - 2);
}

vector<ll> sub;
vector<vector<ll>> adj;

void MakeRoot(int x, int curRoot) {
    if (sub[x] == MOD - 1) {
        sub[curRoot] = 1;
        for (int i: adj[curRoot]) {
            if (i != x) {
                sub[curRoot] = mult(sub[curRoot], sub[i] + 1);
            }
        }
    } else {
        sub[curRoot] = mult(sub[curRoot], inv(sub[x] + 1));
    }
    sub[x] = mult(sub[curRoot] + 1, sub[x]);
}

void rec(int curNode, int prevNode) {
    sub[curNode] = 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            rec(i, curNode);
            sub[curNode] = mult(sub[curNode], sub[i] + 1);
        }
    }
}

vector<ll> ans;

void comp(int curNode, int prevNode) {
    ans[curNode] = sub[curNode];
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            MakeRoot(i, curNode);
            comp(i, curNode);
            MakeRoot(curNode, i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    adj.resize(n);
    sub.resize(n);
    ans.resize(n);
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        u--;
        adj[i].push_back(u), adj[u].push_back(i);
    }
    rec(0, -1);
    comp(0, -1);
    for (int i: ans) {
        cout << i << ' ';
    }
}
