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
//
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")

using namespace std;

struct Updates{
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

    void join0(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    void join1(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        myStack.push({x, parent[x], y, compSize[y]}), cntr++;
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
    vector<int> w;
    for (auto &p: edges) w.push_back(p.second);
    for (auto &v: blocks) for (auto &q: v) w.push_back(q.w);
    sort(w.begin(), w.end());
    int prev = -1;
    int cntr = 0;
    map<int,int> myMap;
    for (int i = 0; i < w.size(); i++) {
        if (w[i] != prev) {
            prev = w[i];
            myMap[w[i]] = cntr++;
        }
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
        edges.emplace_back(make_pair(x, y), z);
    }
    int Q;
    cin >> Q;
    vector<vector<Query>> blocks;
    blocks.emplace_back();
    for (int i = 0; i < Q; i++) {
        if (blocks.back().size() > 1250) {
            blocks.emplace_back();
        }
        int t, w, x;
        cin >> t >> x >> w;
        t--;
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
            if (!q.type) {
                uncertain.push_back(q.x);
                cnt[q.x]++;
            }
        }
        vector<pair<int,int>> myStack;
        vector<int> mnt[v.size()];
        for (int i = 0; i < v.size(); i++) {
            if (!v[i].type) {
                default_edges[v[i].x] = v[i].w;
                myStack.emplace_back(v[i].x, v[i].w);
            } else {
                for (int j: uncertain) {
                    if (default_edges[j] >= v[i].w) {
                        mnt[i].push_back(j);
                    }
                }
            }
        }
        for (int i = myStack.size() - 1; i >= 0; i--) {
            default_edges[myStack[i].first] = myStack[i].second;
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
            Query &q = v[ind];
            if (!q.type) {
                continue;
            }
            for (int i = q.w; i < prev; i++) {
                for (int j: e[i]) {
                    dsu.join0(edges[j].first.first, edges[j].first.second);
                }
            }
            prev = q.w;
            dsu.cntr = 0;
            for (int x: mnt[v[ind].q - total]) {
                dsu.join1(edges[x].first.first, edges[x].first.second);
            }
            myVec.emplace_back(q.q, dsu.getNeighbors(q.x));
            dsu.revert(dsu.cntr);
        }
        sort(v.begin(), v.end(), comp_index);
        for (Query &q: v) {
            if (!q.type) {
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
