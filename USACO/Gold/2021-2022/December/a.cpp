#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;
struct Checker {
    int n;
    vector<vector<int>> adj;
    vector<char> color;
    vector<int> parent;
    int cycle_start, cycle_end;

    bool dfs(int v) {
        color[v] = 1;
        for (int u : adj[v]) {
            if (color[u] == 0) {
                parent[u] = v;
                if (dfs(u))
                    return true;
            } else if (color[u] == 1) {
                cycle_end = v;
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }

    bool find_cycle() {
        color.assign(n, 0);
        parent.assign(n, -1);
        cycle_start = -1;

        for (int v = 0; v < n; v++) {
            if (color[v] == 0 && dfs(v))
                break;
        }

        if (cycle_start == -1) {
            return true;
        } else {
            vector<int> cycle;
            cycle.push_back(cycle_start);
            for (int v = cycle_end; v != cycle_start; v = parent[v])
                cycle.push_back(v);
            cycle.push_back(cycle_start);
            reverse(cycle.begin(), cycle.end());
            return false;
        }
    }
};
bool contiguous (set<int> s) {
    if (s.empty()) return true;
    vector<int> v;
    for (int i: s) {
        v.push_back(i);
    }
    return (v.size() == v.back() - v[0] + 1);
}
void solve () {
    int N, M;
    cin >> N >> M;
    bool fine = true;
    vector<set<int>> adj(2 * N + 1);
    vector<set<int>> adj2(2 * N + 1);
    map<int,set<int>> myMap;
    for (int i = 0; i < M; i++) {
        int n;
        cin >> n;
        int p[n];
        map<int,vector<int>> oc;
        for (int j = 0; j < n; j++) {
            cin >> p[j];
            oc[p[j]].push_back(j);
            myMap[p[j]].insert(i);
        }
        for (auto& p1: oc) {
            if (p1.second.size() != 2) {
                fine = false;
                continue;
            }
            for (auto& p2: oc) {
                int l1 = p1.second[0]; int r1 = p1.second[1];
                int l2 = p2.second[0]; int r2 = p2.second[1];
                if (p2.first == p1.first) {
                    continue;
                }
                if (l1 > l2 && r1 < r2) {
                    adj[p1.first].insert(p2.first);
                } else if (l1 < l2 && r1 > r2) {

                } else if (l2 > l1 && l2 < r1) {
                    fine = false;
                }
                if (l1 <= r1 && r1 <= l2 && l2 <= r2) {
                    adj2[p1.first].insert(p2.first);
                }
            }
        }
    }
    if (!fine) {
        cout << "NO\n";
        return;
    }
    vector<vector<int>> new_adj(2 * N + 1), new_adj1(2 * N + 1);
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            new_adj[i].push_back(j);
        }
        for (int j: adj2[i]) {
            new_adj1[i].push_back(j);
        }
    }
    Checker c;
    c.n = adj.size();
    c.adj = new_adj;
    if (!c.find_cycle()) {
        cout << "NO\n";
        return;
    }
    c.adj = new_adj1;
    if (!c.find_cycle()) {
        cout << "NO\n";
        return;
    }
    for (int i = 0; i <= 2 * N + 1; i++) {
        if (!contiguous(myMap[i])) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";

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
