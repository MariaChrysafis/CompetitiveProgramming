#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
 
using namespace std;
vector<vector<pair<int, int>>> sub;
vector<vector<int>> adj;
vector<int> v;
 
void dfs(int curNode, int prevNode) {
    vector<int> children;
    vector<pair<int, int>> left, right;
    for (int i: adj[curNode]) {
        if (i == prevNode) {
            continue;
        }
        dfs(i, curNode);
        for (auto &p: sub[i]) {
            if (p.first <= v[curNode] && v[curNode] <= p.second) {
                continue;
            }
            if (p.first < v[curNode]) left.emplace_back(p);
            else right.emplace_back(p);
        }
    }
    map<int, int> dpL, dpR;
    dpL[v[curNode]] = dpR[v[curNode]] = 1;
    sort(left.begin(), left.end()); reverse(left.begin(), left.end());
    for (auto &p: left) {
        dpL[p.first] += dpL[p.second + 1] ;
    }
    sort(right.begin(), right.end());
    for (auto &p: right) {
        dpR[p.second] += dpR[p.first - 1];
    }
    set<pair<int, int>> myMap;
    for (auto &l: dpL) {
        for (auto &r: dpR) {
            if (l.second * r.second != 0) {
                myMap.insert({l.first, r.first});
            }
        }
    }
    for (auto &p: myMap) {
        sub[curNode].push_back(p);
    }
 
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    adj.resize(N);
    v.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        v[i]--;
    }
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y), adj[y].push_back(x);
    }
    sub.resize(N);
    dfs(0, -1);
    int ans = 0;
    for (auto &p: sub[0]) {
        ans ++;
    }
    cout << ans << '\n';
 
}
