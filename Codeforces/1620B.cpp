#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;
bool compx (pair<ll,ll> p1, pair<ll,ll> p2) {
    return (p1.first < p2.first);
}
bool compy (pair<ll,ll> p1, pair<ll,ll> p2) {
    return (p1.second < p2.second);
}
ll area (pair<ll,ll> p1, pair<ll,ll> p2, pair<ll,ll> p3) {
    return (p1.first * p2.second + p2.first * p3.second + p3.first * p1.second - p2.first * p1.second - p3.first * p2.second - p1.first * p3.second);
}
void solve() {
    ll w, h;
    cin >> w >> h;
    vector<vector<pair<ll,ll>>> points;
    for (int i = 0; i < 4; i++) {
        points.emplace_back();
        ll n;
        cin >> n;
        points[i].resize(n);
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                cin >> points[i][j].second; points[i][j].first = 0;
            } else if (i == 1) {
                cin >> points[i][j].second; points[i][j].first = h;
            } else if (i == 2) {
                cin >> points[i][j].first; points[i][j].second = 0;
            } else if (i == 3) {
                cin >> points[i][j].first; points[i][j].second = w;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++)  {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                continue;
            }
            ans = max(area(points[i][0], points[i].back(), points[j][0]), ans);
            ans = max(area(points[i][0], points[i].back(), points[j].back()), ans);
        }
        int sz = abs(points[i][0].first - points[i].back().first) + abs(points[i][0].second - points[i].back().second);
        if (i == 0 || i == 1) ans = max(sz * h, ans);
        else ans = max(sz * w, ans);
    }
    cout << ans << '\n';
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
