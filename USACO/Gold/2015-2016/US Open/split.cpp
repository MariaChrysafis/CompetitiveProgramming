#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>

#define ll long long

using namespace std;
struct Point {
    ll x, y;
};
Point read() {
    Point p;
    cin >> p.x >> p.y;
    return p;
}
bool compX(Point p1, Point p2) {
    return (p1.x < p2.x);
}
vector<ll> minY (vector<Point> vec) {
    vector<ll> v;
    v.push_back(vec[0].y);
    for (int i = 1; i < vec.size(); i++) {
        v.push_back(min(v.back(), vec[i].y));
    }
    return v;
}
vector<ll> maxY (vector<Point> vec) {
    vector<ll> v;
    v.push_back(vec[0].y);
    for (int i = 1; i < vec.size(); i++) {
        v.push_back(max(v.back(), vec[i].y));
    }
    return v;
}
ll solve(vector<Point> vec) {
    sort(vec.begin(), vec.end(), compX);
    vector<ll> pref_miY = minY(vec);
    vector<ll> pref_maY = maxY(vec);
    reverse(vec.begin(), vec.end());
    vector<ll> suf_miY = minY(vec);
    vector<ll> suf_maY = maxY(vec);
    reverse(suf_miY.begin(), suf_miY.end());
    reverse(suf_maY.begin(), suf_maY.end());
    reverse(vec.begin(), vec.end());
    ll myMin = LLONG_MAX;
    for (int i = 1; i < vec.size(); i++) {
        ll r1 = abs(pref_maY[i - 1] - pref_miY[i - 1]) * abs(vec[i - 1].x - vec[0].x);
        ll r2 = abs(suf_maY[i] - suf_miY[i]) * abs(vec.back().x - vec[i].x);
        myMin = min(myMin, r1 + r2);
    }
    return (abs(vec[0].x - vec.back().x) * abs(pref_maY.back() - pref_miY.back()) - myMin);
}
int main() {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    int t;
    cin >> t;
    vector<Point> v;
    while (t--) {
        v.push_back(read());
    }
    ll ans = LLONG_MAX;
    ans = min(ans, solve(v));
    for (int i = 0; i < v.size(); i++) {
        swap(v[i].x, v[i].y);
    }
    ans = max(ans, solve(v));
    cout << ans << endl;

}
