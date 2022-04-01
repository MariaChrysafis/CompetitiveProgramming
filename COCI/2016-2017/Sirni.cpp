#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>
 
using namespace std;
 
class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }
 
public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
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
 
    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }
 
    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N); 
    for (int i = 0; i < N; i++) {
        cin >> v[i]; 
    }
    sort(v.begin(),v.end()); v.resize(unique(v.begin(),v.end()) - v.begin());
    DisjointSetUnion dsu(N);
    int MX = 0;
    for (int i = 0; i < N; i++) {
        MX = max(MX, v[i]);
    }
    MX++;
    int lb[MX + 1]; for (int i = 0; i <= MX; i++) lb[i] = -1;
    for (int i = 0; i < N; i++) {
        lb[v[i]] = i;
    }
    for (int i = MX - 1; i >= 1; i--) {
        if (lb[i] != -1) {
            continue;
        }
        lb[i] = lb[i + 1];
    }
    int64_t tot = 0;
    vector<pair<int,int>> edges[MX + 1];
    for (int i = 0; i < N; i++) {
        if (i != N - 1) {
            edges[v[i + 1] % v[i]].emplace_back(i, i + 1);
        }
        for (int mx = v[i]; mx < MX; mx += v[i]) {
            if (lb[mx] == -1) continue;
            edges[v[lb[mx]] % v[i]].emplace_back(lb[mx], i);
        }
    }
    for (int i = 0; i <= MX; i++) {
        for (auto& e: edges[i]) {
            if (dsu.comp(e.first, e.second)) {
                continue;
            }
            dsu.join(e.first, e.second);
            tot += i;
        }
    }
    cout << tot;
 
}
