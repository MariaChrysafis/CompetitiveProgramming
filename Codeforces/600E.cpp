#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
struct Node {
    map<int,int> oc;
    int freq = 0; //frequency of most frequent color
    ll col = 0; //sum of colors
};
Node& merge (Node a, Node& b) {
    if (a.oc.size() > b.oc.size()) {
        swap(a, b);
    }
    for (auto& p: a.oc) {
        b.oc[p.first] += p.second;
        if (b.oc[p.first] > b.freq) {
            b.freq = b.oc[p.first];
            b.col = p.first;
        } else if (b.oc[p.first] == b.freq) {
            b.col += p.first;
        }
    }
    return b;
}
vector<ll> c;
vector<vector<int>> adj;
vector<ll> vec;
Node dfs (int curNode, int prevNode) {
    //cout << curNode << " " << prevNode << '\n';
    Node ans;
    ans.oc[c[curNode]]++;
    ans.freq = 1;
    ans.col = c[curNode];
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            ans = merge(dfs(i, curNode), ans);
        }
    }
    vec[curNode] = ans.col;
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    c.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vec.resize(n);
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << vec[i] << ' ';
    }
}
