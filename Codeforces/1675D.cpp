#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> > vec;
vector<int> dum;
void dfs (vector<vector<int> >& adj, int x) {
    int cntr = 0;
    for (int i: adj[x]) {
        cntr++;
        if (cntr != 1 || vec.empty()) vec.emplace_back();
        vec.back().push_back(i);
        dfs (adj, i);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        vec.clear();
        int n;
        cin >> n;
        vector<vector<int> > adj(n);
        int rt = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            x--;
            if (x != i) {
                adj[x].push_back(i);
            } else {
                rt = x;
            }
        }
        vec.emplace_back();
        vec.back().push_back(rt);
        dfs(adj, rt);
        cout << vec.size() << '\n';
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].size() << '\n';
            for (int j: vec[i]) {
                cout << j + 1 << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}
