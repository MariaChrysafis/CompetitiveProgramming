#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
 
using namespace std;
 
class Updates {
public:
    int parentInd;
    int prev_parent;
    int compInd;
    int prev_comp;
};
 
class DisjointSetUnion {
private:
    vector<int> parent;
    vector<int> compSize;
    int n;
    int connectedComponents;
    stack<Updates> myStack;
public:
    int cntr = 0;
    int getConnectedComponents() const {
        return connectedComponents;
    }
 
    int getNeighbors(int x) {
        return compSize[find_head(x)];
    }
 
public:
    void resz(int sz) {
        n = sz;
        connectedComponents = sz;
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }
 
    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }
 
    void join(int x, int y, bool b) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        if (b) myStack.push({x, parent[x], y, compSize[y]}), cntr++;
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }
 
    void revert(int x) {
        while (x--) {
            Updates u = myStack.top();
            myStack.pop();
            parent[u.parentInd] = u.prev_parent;
            compSize[u.compInd] = u.prev_comp;
            connectedComponents++;
        }
    }
 
    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
 
class Query {
public:
    int w;
    int x;
    int type;
    int q;
 
    Query(int w, int x, int type, int q) {
        this->w = w, this->x = x, this->type = type, this->q = q;
    }
 
    bool operator<(const Query myQuery) const {
        if (myQuery.w != w) return (myQuery.w < w);
        if (myQuery.x != x) return (myQuery.x < x);
        if (myQuery.type != type) return (myQuery.type < type);
        return false;
    }
};
 
bool comp_index(Query a, Query b) {
    return (a.q < b.q);
}
 
void compress(vector<pair<pair<int, int>, int>> &edges, vector<vector<Query>> &blocks) {
    set<int> w;
    for (auto &p: edges) w.insert(p.second);
    for (auto &v: blocks) for (auto &q: v) w.insert(q.w);
    map<int, int> myMap;
    int cntr = 0;
    for (int i: w) {
        myMap[i] = cntr++;
    }
    for (int i = 0; i < edges.size(); i++) {
        edges[i].second = myMap[edges[i].second];
    }
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].w = myMap[blocks[i][j].w];
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        edges.push_back({{x, y}, z});
    }
    int Q;
    cin >> Q;
    vector<vector<Query>> blocks;
    blocks.emplace_back();
    for (int i = 0; i < Q; i++) {
        if (blocks.back().size() > 1000) {
            blocks.emplace_back();
        }
        int t, w, x;
        cin >> t >> x >> w;
        x--;
        blocks.back().emplace_back(Query(w, x, t, i));
    }
    compress(edges, blocks);
    vector<int> default_edges(M);
    for (int i = 0; i < M; i++) {
        default_edges[i] = edges[i].second;
    }
    vector<pair<int, int>> myVec;
    int total = 0;
    for (auto &v: blocks) {
        DisjointSetUnion dsu;
        dsu.resz(N);
        vector<int> uncertain;
        int cnt[M];
        for (int i = 0; i < M; i++) {
            cnt[i] = 0;
        }
        for (Query& q: v) {
            if (q.type == 1) {
                uncertain.push_back(q.x);
                cnt[q.x]++;
            }
        }
        stack<pair<int,int>> myStack;
        vector<int> mnt[v.size()];
        for (int i = 0; i < v.size(); i++) {
            if (v[i].type == 1) {
                default_edges[v[i].x] = v[i].w;
                myStack.push({v[i].x, v[i].w});
            } else {
                for (int j: uncertain) {
                    if (default_edges[j] >= v[i].w) {
                        mnt[i].push_back(j);
                    }
                }
            }
        }
        while (!myStack.empty()) {
            default_edges[myStack.top().first] = myStack.top().second;
            myStack.pop();
        }
        vector<int> e[M + Q];
        for (int i = 0; i < M; i++) {
            if (!cnt[i]) {
                e[default_edges[i]].push_back(i);
            }
        }
        sort (v.begin(), v.end());
        int prev = M + Q;
        for (int ind = 0; ind < v.size(); ind++) {
            Query q = v[ind];
            if (q.type == 1) {
                continue;
            }
            for (int i = q.w; i < prev; i++) {
                for (int j: e[i]) {
                    dsu.join(edges[j].first.first, edges[j].first.second, 0);
                }
            }
            prev = q.w;
            dsu.cntr = 0;
            for (auto& x: mnt[v[ind].q - total]) {
                dsu.join(edges[x].first.first, edges[x].first.second, 1);
            }
            myVec.emplace_back(q.q, dsu.getNeighbors(q.x));
            dsu.revert(dsu.cntr);
        }
        sort(v.begin(), v.end(), comp_index);
        for (Query &q: v) {
            if (q.type == 1) {
                default_edges[q.x] = q.w;
            }
        }
        total += v.size();
    }
 
    sort(myVec.begin(), myVec.end());
    for (auto &p: myVec) {
        cout << p.second << '\n';
    }
}
