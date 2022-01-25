#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

void merge(pair<map<int, int>, int> &x, pair<map<int, int>, int> y) {
    if (x.first.size() < y.first.size()) {
        swap(x, y);
    }
    for (auto &p: y.first) {
        x.first[p.first] += p.second;
        if ((x.first[p.first] > x.first[x.second]) || (x.first[p.first] == x.first[x.second] && p.first < x.second)) {
            x.second = p.first;
        }
    }
}

vector<vector<int>> adj;
vector<int> res;

pair<map<int, int>, int> rec(int curNode, int prevNode, int depth) {
    pair<map<int, int>, int> ans;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            merge(ans, rec(i, curNode, depth + 1));
        }
    }
    pair<map<int, int>, int> m1;
    m1.first[depth]++;
    m1.second = depth;
    merge(ans, m1);
    res[curNode] = ans.second - depth;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    adj.resize(N), res.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    rec(0, -1, 0);
    for (int i: res) {
        cout << i << '\n';
    }
}
