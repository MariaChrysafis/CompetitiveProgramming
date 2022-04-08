#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>


using namespace std;

class Node {
public:
    unordered_map<int,int> myMap;
    int sz = 1;
    int len;
};

vector<int> tot;

void merge (Node x, Node &y, int depth) {
    if (x.sz > y.sz) {
        swap(x, y);
    }
    y.myMap.reserve((5 * (x.myMap.size() + y.myMap.size()))/2);
    y.len = max(y.len, x.len);
    for (auto& p: x.myMap) {
        for (int i: tot) {
            if (y.myMap.count(p.first ^ i)) {
                y.len = max(y.len, p.second + y.myMap[(p.first ^ i)] - 2 * depth);
            }
        }
    }
    for (auto& p: x.myMap) {
        y.sz += (!y.myMap[p.first]);
        y.myMap[p.first] = max(y.myMap[p.first], p.second);
    }
}

class Tree {
public:
    vector<vector<int>> adj;
    vector<int> weight;
    map<pair<int,int>,int> m3d3;
    vector<int> res;
    void do_once (int curNode, int prevNode) {
        weight[curNode] = weight[prevNode] ^ m3d3[{curNode, prevNode}];
        for (int i: adj[curNode]) if (i != prevNode) do_once(i, curNode);
    }
    void add_edge (int u, int v, char c) {
        adj[u].push_back(v), adj[v].push_back(u);
        m3d3[{u, v}] = m3d3[{v, u}] = (1 << (c - 'a'));
    }
    Node dfs (int curNode, int prevNode, int depth) {
        Node ans; ans.len = 0; ans.myMap[weight[curNode]] = depth;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                merge(dfs (i, curNode, depth + 1), ans, depth);
            }
        }
        res[curNode] = ans.len;
        return ans;
    }
    Tree (int n) {
        adj.resize(n), weight.assign(n, 0), res.resize(n);
    }
    void read () {
        do_once(0, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    Tree myTree(N);
    for (int i = 1; i < N; i++) {
        int u; char c; cin >> u >> c;
        u--;
        myTree.add_edge(u, i, c);
    }
    myTree.read();
    for (int i = 0; i < 22; i++) {
        tot.push_back(1 << i);
    }
    tot.push_back(0);
    myTree.dfs(0, 0, 1);
    for (int i: myTree.res) {
        cout << i << ' ';
    }
    cout << '\n';

}
