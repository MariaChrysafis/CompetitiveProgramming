#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
vector<vector<int> >adj;
vector<int> col;
vector<int> sub;
void dfs (int curNode, int prevNode) {
    sub[curNode] = col[curNode];
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
            sub[curNode] += sub[i];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        adj.clear();
        adj.resize(n);
        col.resize(n);
        sub.assign(n, false);
        for (int i = 1; i < n; i++) {
            int u;
            cin >> u;
            u--;
            adj[u].push_back(i), adj[i].push_back(u);
        }
        string s;
        cin >> s;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'W') col[i] = 1;
            else col[i] = -1;
        }
        dfs(0, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (sub[i] == 0);
        }
        cout << ans << '\n';
    }
}
