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

#define ll long long
using namespace std;
const int MOD = (int) 998244353;
vector<vector<int>> adj;
vector<vector<int>> comp;
map<int,bool> marked;
void dfs (int curNode) {
    if (marked[curNode]) {
        return;
    }
    marked[curNode] = true;
    comp.back().push_back(curNode);
    for (int i: adj[curNode]) {
        dfs(i);
    }
}
vector<int> ans;
void merge (vector<int> v1, vector<int> v2) {
    vector<int> pos(v1.size() + v2.size());
    for (int i = 0; i < v1.size(); i++) {
        pos[2 * i] = v1[i];
    }
    for (int i = 0; i < v2.size(); i++) {
        pos[2 * i + 1] = v2[i];
    }
    for (int i = 0; i < pos.size(); i++) {
        ans[pos[(i - 1 + pos.size()) % pos.size()]] = pos[i];
    }
}
void generate (vector<int> v) {
    if (v.size() == 1) {
        ans[v[0]] = v[0];
        return;
    }
    //we have some sequence v
    vector<int> rel(v.size());
    vector<int> first, second;
    for (int i = 0; i < (v.size() + 1)/2; i++) {
        first.push_back(i);
    }
    for (int i = (v.size() + 1)/2; i < v.size(); i++) {
        second.push_back(i);
    }
    vector<int> pos(v.size());
    for (int i = 0; i < first.size(); i++) {
        pos[2 * i] = v[first[i]];
    }
    for (int i = 0; i < second.size(); i++) {
        pos[2 * i + 1] = v[second[i]];
    }
    for (int i = 0; i < pos.size(); i++) {
        ans[pos[(i - 1 + pos.size()) % pos.size()]] = pos[i];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    adj.resize(n), ans.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
        adj[i].push_back(v[i]);
    }
    for (int i = 0; i < n; i++) {
        if (!marked[i]) {
            comp.push_back({});
            dfs(i);
        }
    }
    map<int,vector<int>> myMap;
    for (int i = 0; i < comp.size(); i++) {
        myMap[comp[i].size()].push_back(i);
    }
    for (auto& p: myMap) {
        if (p.first % 2 == 1) continue;
        if (p.second.size() % 2 == 1) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 0; i < comp.size(); i++) {
        if (comp[i].size() % 2 == 1) {
            generate(comp[i]);
        }
    }
    for (auto& p: myMap) {
        if (p.first % 2 == 1) continue;
        vector<int> vec = p.second;
        for (int i = 0; i < vec.size(); i += 2) {
            merge(comp[vec[i]], comp[vec[i + 1]]);
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << ' ';
    }
}
