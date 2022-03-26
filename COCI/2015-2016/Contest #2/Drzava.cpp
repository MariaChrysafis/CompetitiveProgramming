#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O2")
#pragma GCC optimization ("unroll-loops")
#include <limits.h>
using namespace std;
vector<pair<pair<int64_t,int64_t>,pair<int,int>>> vec;
int64_t lst = 0;
class DisjointSetUnion {
protected:
    vector<int> parent;
    int k;
    vector<int> pos;
    int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    int merge (int x, int y) {
        for (int i = 0; i < k; i++) {
            if ((x & (1 << i)) && (y & (1 << (k - i)))) {
                cout << fixed << setprecision(3) << sqrt(lst) << '\n';
                exit(0);
            }
        }
        int ans = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (ans & (1 << (i + j) % k)) {
                    continue;
                }
                if ((x & (1 << i)) && (y & (1 << j))) {
                    ans += (1 << (i + j) % k);
                }
            }
        }
        return ans;
    }
    DisjointSetUnion(int sz, int K) {
        n = sz;
        parent.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        this->k = K;
        pos.resize(sz);
        for (int i = 0; i < sz; i++) {
            pos[i] = (1 << vec[i].second.second) + 1;
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
        parent[x] = y;
        pos[y] = merge(pos[y], pos[x]);
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};
int64_t dist (pair<pair<int64_t,int64_t>,pair<int,int>> p1, pair<pair<int64_t,int64_t>,pair<int,int>> p2) {
    int64_t d = abs(p1.first.first - p2.first.first) * abs(p1.first.first - p2.first.first);
    d += abs(p1.first.second - p2.first.second) * abs(p1.first.second - p2.first.second);
    return d;
}
bool cmp (pair<int,int> p1, pair<int,int> p2) {
    return (dist(vec[p1.first], vec[p1.second]) < dist(vec[p2.first], vec[p2.second]));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vec.resize(N);
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first.first >> vec[i].first.second;
        vec[i].second.first = i;
        cin >> vec[i].second.second; vec[i].second.second %= K;
    }
    sort(vec.begin(), vec.end());
    DisjointSetUnion dsu(N, K);
    vector<pair<int,int>> edges;
    for (int i = 0; i < N; i++) {
        for (int j = max(i - K, 0); j <= min(i + K, N - 1); j++) {
            edges.push_back({i, j});
        }
    }
    sort(edges.begin(), edges.end(), cmp);
    for (auto& p: edges) {
        if (dsu.comp(p.first, p.second)) continue;
        lst = dist(vec[p.first], vec[p.second]);
        //cout << dist(vec[p.second.first])
        dsu.join(p.first, p.second);
    }
}
