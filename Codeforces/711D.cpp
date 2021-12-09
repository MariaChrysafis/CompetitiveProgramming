#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
using namespace std;
const int MAX = 2e5 + 10;
int n;
vector<int> f;
int dp[MAX][30];
int sz[MAX];
int id[MAX];
int dist[MAX];
ll MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    f.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i]; f[i]--;
    }
    for (int i = 0; i < n; i++) {
        if (f[i] == i) {
            cout << 0;
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = f[i];
    }
    for (int j = 1; j < 30; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    bool cycle[n]; //these are all the elements which belong to a cycle
    for (int i = 0; i < n; i++) {
        cycle[i] = false;
    }
    for (int i = 0; i < n; i++) {
        cycle[dp[i][29]] = true;
    }
    for (int i = 0; i < n; i++) {
        if (!cycle[i]) {
            continue;
        }
        for (int j = 0; j < 30; j++) {
            cycle[dp[i][j]] = true;
        }
    }
    ll ans = 1;
    int edges = 0;
    for (int i = 0; i < n; i++) {
        if (!cycle[i]) {
            continue;
        }
        ll powr = 1;
        int curNode = i;
        int curDist = 1;
        vector<int> nodes;
        while (!dist[curNode]) {
            cycle[curNode] = true;
            id[curNode] = i;
            dist[curNode] = curDist++;
            curNode = f[curNode];
            nodes.push_back(curNode);
            powr *= 2;
            powr %= MOD;
        }
        for (int j: nodes) {
            sz[j] = curDist;
        }
        if (powr > 2) {
            powr -= 2;
            ans *= powr;
            ans %= MOD;
        }
        edges++;
    }
    edges = n - edges;
    while (edges--) {
        ans *= 2;
        ans %= MOD;
    }
    cout << ans;



}
