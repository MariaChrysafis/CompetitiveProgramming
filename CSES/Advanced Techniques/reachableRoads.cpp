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
vector<bitset<50000>> bs;
vector<vector<int>> adj;
void rec (int curNode) {
    if (bs[curNode].count() != 0) {
        return;
    }
    bs[curNode].set(curNode);
    for (int i: adj[curNode]) {
        rec(i);
        bs[curNode] = bs[curNode] | bs[i];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    bs.resize(N), adj.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }
    for (int i = 0; i < N; i++) {
        rec(i);
    }
    for (int i = 0; i < N; i++) {
        cout << bs[i].count() << ' ';
    }
 
 
}
