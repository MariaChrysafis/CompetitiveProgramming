#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
set<int> solve(vector<vector<int>> adj) {
    set<int> I;
    set<int> V;
    for (int i = 0; i < adj.size(); i++) {
        V.insert(i);
    }
    while (!V.empty()) {
        auto it = V.begin();
        int x = (int)(random() * 100) % V.size();
        while(x--) {
            it++;
        }
        int choice = *it;
        I.insert(choice);
        V.erase(V.find(choice));
        for (int i: adj[choice]) {
            if (V.count(i)) {
                V.erase(V.find(i));
            }
        }
    }
    return I;
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    set<int> best;
    int t = 100;
    while(t--) {
        set<int>s = solve(adj);
        if (s.size() > best.size()) {
            best = s;
        }
        //cout << s.size() << endl;
    }
    cout << best.size() << '\n';
    for (int i: best) {
        cout << i << ' ';
    }
    cout << '\n';
}
