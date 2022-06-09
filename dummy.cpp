#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
struct Graph {
    vector<int> adj[26];
    vector<bool> pos;
    void add_edge (char u, char v) {
        adj[u - 'a'].push_back(v - 'a');
    }
    bool hasCycle () {
        vector<int> in_deg;
        in_deg.assign(26, false);
        pos.assign(26, false);
        int cntr = 0;
        for (int i = 0; i < 26; i++) {
            for (int j: adj[i]) {
                in_deg[j]++;
                pos[i] = pos[j] = true;
            }
        }
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (in_deg[i] == 0 && pos[i]) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front();
            cntr++;
            q.pop();
            for (int i: adj[x]) {
                in_deg[i]--;
                if (in_deg[i] == 0) {
                    q.push(i);
                }
            }
        }
        for (bool i: pos) {
            cntr -= i;
        }
        return (cntr == 0);
    }
};
int main() {
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<string> arr(n);
    vector<vector<int64_t> > pref(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    multiset<int> tot;
    set<int> lst;
    for (int i = 0; i < n; i++) {
        pref[i].resize(arr[i].size() + 1);
        pref[i][0] = 0;
        for (int j = 1; j <= arr[i].size(); j++) {
            pref[i][j] = (30 * pref[i][j - 1] + arr[i][j - 1]) % MOD;
            tot.insert(pref[i][j]);
        }
        lst.insert(pref[i].back());
    }
    vector<string> ans;
    for (int i = 0; i < n; i++) {
        Graph gr;
        for (int j = 0; j < arr[i].size(); j++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (c != arr[i][j] && tot.count((pref[i][j] * 30 + c) % MOD)) {
                    gr.add_edge(c, arr[i][j]);
                }
            }
            if (lst.count(pref[i][j])) {
                gr.add_edge('a', 'b'), gr.add_edge('b', 'a');
            }
        }
        if (gr.hasCycle()) {
            ans.push_back(arr[i]);
        }
    }
    cout << ans.size() << '\n';
    for (string s: ans) {
        cout << s << '\n';
    }
}
