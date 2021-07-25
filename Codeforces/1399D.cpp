#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> v;
    set<int> ending[2];
    for (int i = 0; i < n; i++) {
        int b = s[i] - '0';
        if (ending[!b].empty()) {
            v.push_back({i});
            ending[b].insert(v.size() - 1);
        } else {
            int x = *ending[!b].begin();
            //cout << x << " " << v.size() << endl;
            v[x].push_back(i);
            //cout << i << endl;
            ending[b].insert(x);
            ending[!b].erase(x);
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            ans[v[i][j]] = i;
        }
    }
    cout << v.size() << endl;
    for (int i: ans) {
        cout << i + 1 << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
