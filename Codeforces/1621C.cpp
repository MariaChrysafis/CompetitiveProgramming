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

typedef int64_t ll;
vector<int> q = {1, 2, 3, 4, 5};
vector<int> p = {1, 3, 2, 5, 4};
void print () {
    for (int i: q) {
        cout << i << ' ';
    }
    cout << '\n';
}
/*
int query (int ind) {
    cout << "? " << ind << '\n';
    int val = q[ind];
    vector<int> new_q(q.size());
    for (int i = 0; i < p.size(); i++) {
        new_q[i] = q[p[i] - 1];
    }
    q = new_q;
    return val - 1;
}
 */
int query (int ind) {
    cout << "? " << ind + 1 << '\n';
    cout.flush();
    int x;
    cin >> x;
    x--;
    return x;
}
void solve () {
    int n;
    cin >> n;
    set<int> s;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        if (s.count(i)) {
            continue;
        }
        vector<int> values;
        while (true) {
            int val = query(i);
            if (s.count(val)) {
                break;
            }
            s.insert(val);
            values.push_back(val);
        }
        for (int j = 0; j < values.size(); j++) {
            adj[values[j]].push_back(values[(j + 1) % values.size()]);
        }
    }
    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << adj[i][0] + 1 << ' ';
    }
    cout << '\n';
    cout.flush();
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
