#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
int64_t gcd (int64_t u, int64_t v) {
    if (!u || !v) return max(u, v);
    return gcd(max(u, v) % min(u, v), min(u, v));
}
pair<int64_t,int64_t> frac (pair<int64_t,int64_t> p) {
    assert(p.first != 0 || p.second != 0);
    if (p.first == 0) return {0, 1};
    if (p.second == 0) return {1, 0};
    if (p.first < 0 && p.second < 0) p.first = -p.first, p.second = -p.second;
    int64_t g = gcd(abs(p.first), abs(p.second));
    return make_pair(p.first/g, p.second/g);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int64_t,int64_t>> points(n);
    for (int i = 0; i < points.size(); i++) {
        cin >> points[i].first >> points[i].second;
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<int64_t,int64_t>> new_points;
        map<pair<int64_t,int64_t>,int64_t> cnt;
        for (auto& p: points) {
            if (p == points[i]) {
                continue;
            }
            cnt[frac(make_pair(p.first - points[i].first, p.second - points[i].second))]++;
        }
        for (auto& p: cnt) {
            if ((p.first.first > 0) == (p.first.second > 0)) {
                ans += (cnt[make_pair(-p.first.second, p.first.first)] + cnt[make_pair(p.first.second, -p.first.first)]) * p.second;
            }
        }
        ans += cnt[{1, 0}] * cnt[{0, 1}];
        ans += cnt[{1, 0}] * cnt[{0, -1}];
        ans += cnt[{-1, 0}] * cnt[{0, 1}];
        ans += cnt[{-1, 0}] * cnt[{0, -1}];
    }
    cout << ans;


}
