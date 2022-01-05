#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;
typedef long long ll;

struct Tree {
    vector<vector<int>> adj;
    vector<int> parent, st, en, euler, depth;
    int cntr = 0;

    void resz(int n) {
        adj.resize(n), parent.resize(n), st.resize(n), en.resize(n), depth.resize(n);
    }

    void dfs(int curNode, int prevNode) {
        parent[curNode] = prevNode;
        euler.push_back(curNode);
        st[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
        euler.push_back(curNode);
        en[curNode] = cntr++;
    }

    void find_depths() {
        int src = 0;
        queue<pair<int, int>> q;
        q.push({src, 1});
        while (!q.empty()) {
            int curNode = q.front().first;
            int curDist = q.front().second;
            q.pop();
            if (depth[curNode]) {
                continue;
            }
            depth[curNode] = curDist++;
            for (int i: adj[curNode]) {
                q.push({i, curDist});
            }
        }
    }
};

vector<ll> powr;

void fill_powr() {
    powr.push_back(1);
    while (powr.size() != 27) {
        powr.push_back(powr.back() * 2);
    }
}

Tree t;

int findFirstExceeds(vector<int> &v, int X) {
    //find the first index in v which exceeds X
    if (v.empty() || v.back() < X) {
        return -1;
    }
    int l = 0;
    int r = v.size() - 1;
    while (l != r) {
        int m = (l + r) / 2;
        if (v[m] >= X) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int findLastSmaller(vector<int> &v, int X) {
    if (v.empty() || v[0] > X) {
        return -1;
    }
    int l = 0;
    int r = v.size() - 1;
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (v[m] <= X) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fill_powr();
    int N, Q;
    cin >> N >> Q;
    t.resz(N);
    t.parent[0] = -1;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        t.adj[i].push_back(--p), t.adj[p].push_back(i);
    }
    t.dfs(0, -1);
    t.find_depths();
    string s;
    cin >> s;
    vector<int> bxor(N);
    for (int i = 0; i < s.length(); i++) {
        bxor[i] = powr[(s[i] - 'a')];
    }
    vector<vector<int>> at_depth(N + 1);
    vector<vector<int>> pref(N + 1);
    for (int i = 0; i < t.euler.size(); i++) {
        if (t.st[t.euler[i]] == i) {
            at_depth[t.depth[t.euler[i]]].push_back(i);
        }
    }
    for (int i = 0; i <= N; i++) {
        pref[i].push_back(0);
        for (int j = 0; j < at_depth[i].size(); j++) {
            pref[i].push_back(pref[i].back() ^ bxor[t.euler[at_depth[i][j]]]);
        }
    }
    while (Q--) {
        int v, h;
        cin >> v >> h;
        v--;
        int l = findFirstExceeds(at_depth[h], t.st[v]);
        int r = findLastSmaller(at_depth[h], t.en[v]);
        if (l == -1 || r == -1) {
            cout << "Yes\n";
            continue;
        }
        int curXor = pref[h][r + 1] ^pref[h][l];
        if (curXor == 0 || __builtin_popcount(curXor) == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
