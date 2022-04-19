#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
#include <queue>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> points(n);
    map<pair<int,int>,pair<int,int>> res;
    set<pair<int,int>> s;
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
        s.insert(points[i]);
    }
    queue<pair<int,int>> pos;
    for (int i = 0; i < n; i++) {
        for (int dx = -1; dx <= 1; dx += 2) {
            if (!s.count({points[i].first + dx, points[i].second})) {
                pos.push(points[i]);
                res[points[i]] = points[i]; res[points[i]].first += dx;
            }
            if (!s.count({points[i].first, points[i].second + dx})) {
                pos.push(points[i]);
                res[points[i]] = points[i]; res[points[i]].second += dx;
            }
        }
    }
    while (!pos.empty()) {
        pair<int,int> p = pos.front();
        pos.pop();
        for (int dx = -1; dx <= 1; dx += 2) {
            if (!s.count({p.first + dx, p.second})) continue;
            if (res.count({p.first + dx, p.second})) continue;
            res[{p.first + dx, p.second}] = res[p];
            pos.push({p.first + dx, p.second});
        }
        for (int dx = -1; dx <= 1; dx += 2) {
            if (!s.count({p.first, p.second + dx})) continue;
            if (res.count({p.first, p.second + dx})) continue;
            res[{p.first, p.second + dx}] = res[p];
            pos.push({p.first, p.second + dx});
        }
    }
    for (int i = 0; i < n; i++) {
        cout << res[points[i]].first << " " << res[points[i]].second << '\n';
    }

}
