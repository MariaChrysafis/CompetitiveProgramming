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
#include <queue>
#include <limits.h>
#include <bitset>
 
using namespace std;
const int MOD = 1e9 + 9;
class DisjointSetUnion {
public:
    DisjointSetUnion (int n) {
        parent.assign(n, 0);
        compSize.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
 
    vector<int> parent, compSize;
 
    int find_head (int x) {
        if (x == parent[x]) {
            return x;
        }
        return find_head(parent[x]);
    }
 
    void join (int a, int b) {
        a = find_head(a);
        b = find_head(b);
        if (compSize[b] > compSize[a]) {
            swap(a, b);
        }
        parent[a] = b;
        compSize[b] = compSize[a] + compSize[b];
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    DisjointSetUnion dsu(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        dsu.join(u, v);
    }
    vector<int> v;
    for (int i = 0; i < N; i++) {
        if (dsu.find_head(i) == i) {
            v.push_back(dsu.compSize[dsu.find_head(i)]);
        }
    }
    bitset<100001> bs;
    bs.set(0);
    for (int i = 0; i < v.size(); i++) {
        bs = bs | (bs << v[i]);
    }
    for (int i = 1; i <= N; i++) {
        cout << bs[i];
    }
    cout << '\n';
 
 
}
