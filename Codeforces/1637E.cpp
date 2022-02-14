#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;
int get_distinct (vector<int> a) {
    set<int> s;
    for (int i: a) {
        s.insert(i);
    }
    return s.size();
}
void solve () {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<pair<int,int>> vec = {{a[0], 1}};
    for (int i = 1; i < n; i++) {
        if (a[i] == vec.back().first) {
            vec.back().second++;
        } else {
            vec.push_back({a[i], 1});
        }
    }
    set<pair<int,int>> bad;
    for (int tc = 0; tc < m; tc++) {
        int x, y; cin >> x >> y;
        bad.insert({min(x, y), max(x, y)});
    }
    vector<int> oc[n + 1];
    for (auto& p: vec) {
        oc[p.second].push_back(p.first);
    }
    for (int i = 0; i <= n; i++) {
        sort(oc[i].begin(), oc[i].end()), reverse(oc[i].begin(), oc[i].end());
    }
    int64_t myMax = 0;
    for (int i = 1; i <= n; i++) {
        for (auto &p1: oc[i]) {
            for (int j = 1; j <= i; j++) {
                for (auto &q1: oc[j]) {
                    if (p1 == q1 || bad.count({min(p1, q1), max(p1, q1)}))continue;
                    myMax = max(myMax, ((int64_t)i + (int64_t)j) * ((int64_t)p1 + (int64_t)q1));
                    break;
                }
            }
        }
    }
    cout << myMax << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve ();
    }
}
