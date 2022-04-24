#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cassert>
#include <climits>
#include "race.h"
using namespace std;
class Tree {
public:
    vector<vector<int>> adj;
    map<pair<int,int>,int64_t> weight;
    vector<bool> hasVisited;
    vector<int> sub;
    vector<int> parent;
    vector<int> gw;
    int sz = 0;
    void prelim (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        gw[curNode] = weight[make_pair(curNode, prevNode)];
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                prelim(i, curNode);
            }
        }
    }
    int get_weight (int curNode, int prevNode) {
        if (parent[curNode] == prevNode) {
            return gw[curNode];
        } else if (parent[prevNode] == curNode){
            return gw[prevNode];
        }
      assert(false);
    }
    int dfs_for_sz (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i]) {
                sub[curNode] += dfs_for_sz (i, curNode);
            }
        }
        return (sz = sub[curNode]);
    }
    int find_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (sub[i] * 2 > sz && !hasVisited[i] && i != prevNode) {
                return find_centroid(i, curNode);
            }
        }
        return curNode;
    }
    map<int64_t,int> tot, exc;
    void dfs (int curNode, int prevNode, int64_t w, int d) {
        if (exc.count(w)) exc[w] = min(exc[w], d);
        else exc[w] = d;
        for (int i: adj[curNode]) {
            if (i != prevNode && !hasVisited[i]) {
                dfs (i, curNode, w + get_weight(i, curNode), d + 1);
            }
        }
    }
    int ans = INT_MAX;
    int64_t k;
    void solve (int curNode) {
        dfs_for_sz(curNode, curNode);
        int centroid = find_centroid(curNode, curNode);
        hasVisited[centroid] = true;
        //Two Cases:
        //(1) It passes through the centroid
        //(2) It doesn't pass through the centroid
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                dfs (i, i, get_weight(i, centroid), 1);
                for (auto& p: exc) {
                    if (tot.count(k - p.first)) {
                        ans = min(ans, tot[k - p.first] + p.second);
                    }
                }
                for (auto& p: exc) {
                    if (tot.count(p.first)) tot[p.first] = min(tot[p.first], p.second);
                    else tot[p.first] = p.second;
                }
                exc.clear();
            }
        }
        if (tot.count(k)) {
            ans = min(ans, tot[k]);
        }
        tot.clear();
        for (int i: adj[centroid]) {
            if (!hasVisited[i]) {
                solve (i);
            }
        }
    }
    void add_weight (int u, int v, int64_t w) {
        weight[make_pair(u, v)] = weight[make_pair(v, u)] = w;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    Tree (int n, int k) {
        adj.resize(n), hasVisited.assign(n, false), sub.assign(n, false), gw.resize(n), parent.resize(n);
        this->k = k;
    }
};
int best_path(int n, int k, int H[][2], int L[]){
    Tree myTree(n, k);
    for (int i = 0; i < n - 1; i++) {
        myTree.add_weight(H[i][0], H[i][1], L[i]);
    }
    myTree.prelim(0, 0);
    myTree.solve(0);
    if (myTree.ans == INT_MAX) return -1;
    return myTree.ans;
}
/*
int main() {
    
}
*/
