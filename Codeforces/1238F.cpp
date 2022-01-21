#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

class Tree {
public:
    int ans = 0;
    Tree(int n) {
        adj.resize(n);
        sub.resize(n);
    }

    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    int read () {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size() != 1) {
                dfs (i, -1);
                return ans;
            }
        }
        return adj.size();
        assert(false);
    }

private:
    vector<vector<int>> adj;
    vector<int> sub;
    /*
     * sub0 -> the minimum cost if we are allowed to take our parent
     * sub1 -> the minimum cost if we are not allowed to take our parent
     */
    int dfs (int curNode, int prevNode) {
        vector<int> pos = {0, 0};
        int children = 0;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                pos.push_back(dfs(i, curNode));
                children++;
            }
        }
        sort(pos.begin(), pos.end());
        ans = max(ans, pos.back() + pos[pos.size() - 2] + (int)adj[curNode].size() + 1);
        return pos.back() + adj[curNode].size() - 1;
    }

};

void solve () {
    int N;
    cin >> N;
    Tree tree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        tree.add_edge(u, v);
    }
    if (N <= 2) {
        cout << N << '\n';
        return ;
    }
    cout << tree.read() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
