#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

set<int> adj[200000];

ll n, m;

vector<vector<int>> cc;
set<int> s;

void dfs (int curNode) {
    cc.back().push_back(curNode);
    s.erase(curNode);
    int prev = -1;
    while (true) {
        auto it = s.upper_bound(prev);
        if (it == s.end()) {
            break;
        }
        prev = *it;
        if (!adj[curNode].count(prev)) {
            dfs(prev);
        }
    }
}

bool comp (pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return (p1.second < p2.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    vector<pair<pair<int,int>,int>> edges(m);
    int XOR = 0;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;
        XOR ^= edges[i].second;
        adj[edges[i].first.first - 1].insert(edges[i].first.second - 1);
        adj[edges[i].first.second - 1].insert(edges[i].first.first - 1);
    }
    for (int i = 0; i < n; i++) {
        s.insert(i);
    }
    map<int,int> component;
    for (int i = 0; i < n; i++) {
        if (s.count(i)) {
            cc.emplace_back();
            dfs (i);
        }
    }
    dsu d, dum;
    d.n = n, dum.n = n;
    d.fill(), dum.fill();
    for (int i = 0; i < cc.size(); i++) {
        for (int j: cc[i]) {
            d.join(j, cc[i][0]);
        }
    }
    sort(edges.begin(), edges.end(), comp);
    int ans = 0;
    int cntr = 0;
    for (auto & p: edges) {
        if (!d.comp(p.first.first - 1, p.first.second - 1)) {
            d.join(p.first.first - 1, p.first.second - 1);
            dum.join(p.first.first - 1, p.first.second - 1);
            ans += p.second;
            cntr++;
        } else if (!dum.comp(p.first.first - 1, p.first.second - 1)) {
            XOR = min(XOR, p.second);
        }
    }
    if (cntr + n * (n - 1)/2 - m != n - 1) {
        XOR = 0;
    }
    cout << ans + XOR << '\n';

}
