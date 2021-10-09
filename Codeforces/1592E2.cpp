#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O2")
using namespace std;
set<long long> marked;
map<long long, int> color;
vector<vector<long long>> adj;
const long long MOD = 1e9 + 7;
long long mult(long long x, long long y) {
    return (x * y) % MOD;
}
long long binPow(long long x, long long y) {
    long long res = x;
    long long ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
            ans %= MOD;
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
map<pair<long long,long long>,long long> dp;
long long solve(long long curNode, long long col, long long sub) {
    if(!marked.count(curNode)) {
        return binPow(4ll, sub - 1);
    }
    if (color[curNode] != col && color[curNode] != 0) {
        return 0;
    }
    if (sub == 1) {
        return 1;
    }
    if (dp.count({curNode, col})) {
        return dp[{curNode, col}];
    }
    long long ans;
    long long x = 0;
    long long y = 0;
    for (int i: adj[col]) {
        x += solve(2 * curNode, i, (sub - 1)/2);
        y += solve(2 * curNode + 1, i, (sub - 1)/2);
    }
    x %= MOD;
    y %= MOD;
    ans = (x * y) % MOD;
    return (dp[{curNode,col}] = ans);
}
long long powr(long long x) {
    long long ans = 1;
    while (x--) {
        ans *= 2;
    }
    return ans;
}
int main() {
    long long k, n;
    cin >> k >> n;
    map<string, long long> myMap;
    myMap["white"] = 1;
    myMap["yellow"] = 2;
    myMap["green"] = 3;
    myMap["blue"] = 4;
    myMap["red"] = 5;
    myMap["orange"] = 6;
    adj.resize(7);
    adj[1] = {3, 4, 5, 6};
    adj[2] = {3, 4, 5, 6};
    adj[3] = {1, 2, 5, 6};
    adj[4] = {1, 2, 5, 6};
    adj[5] = {1, 2, 3, 4};
    adj[6] = {1, 2, 3, 4};
    for (int i = 0; i < n; i++) {
        long long v; string s;
        cin >> v >> s;
        color[v] = myMap[s];
        while(v != 0) {
            marked.insert(v);
            v /= 2;
        }
    }
    long long ans = 0;
    for (int i = 0; i < 6; i++) {
        ans += solve(1, i + 1, powr(k) - 1);
        ans %= MOD;
    }
    cout << ans << endl;
}
