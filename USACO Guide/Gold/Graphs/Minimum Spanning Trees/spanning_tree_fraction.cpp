#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <climits>
#include <iomanip>
#include <queue>
#include <set>
#include <algorithm>
#define ll int
#define ld double
using namespace std;
struct DSU {
    vector<int> e; void init(int N) { e = vector<int>(N,-1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool unite(int x, int y) { // union by size
        x = get(x), y = get(y); if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; e[y] = x; return 1;
    }
};
ld C;
vector<pair<pair<int,int>, pair<int,int>>> vec;
bool comp(int e1, int e2) {
    return -vec[e1].second.first + C * vec[e1].second.second < -vec[e2].second.first + C * vec[e2].second.second;
}
ll A = 0;
ll B = 0;
vector<int> ed;
ld kruskal(int N, ld F) {
    C = F;
    sort(ed.begin(), ed.end(), comp);
    ld ans = 0; DSU D; D.init(N+1);
    A = B = 0;
    for (auto a: ed) {
        if (D.unite(vec[a].first.first,vec[a].first.second)) {
            ans += -vec[a].second.first + F * vec[a].second.second;
            A += vec[a].second.first;
            B += vec[a].second.second;
            if (ans > 0) {
                return 1;
            }
        }
    }
    return ans;
}
int n;
bool valid (ld C) {
    auto p = kruskal(n, C);
    return (p <= 0);
}
ld binSearch (ld l, ld r, int cntr) {
    ld m = (l + r)/2;
    if (cntr == 55) {
        return l;
    }
    if (valid(m)) {
        return binSearch(m, r, ++cntr);
    } else {
        return binSearch(l, m , ++cntr);
    }
}
ll gcd (ll x, ll y) {
    if (min(x,y) == 0) return max(x,y);
    return gcd(max(x,y) % min(x,y), min(x,y));
}
int main() {
//    freopen("art2.in", "r", stdin);
//    freopen("art2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        vec.push_back({{a, b}, {c,d}});
        vec.push_back({{b, a}, {c, d}});
    }
    for (int i = 0; i < vec.size(); i++) {
        ed.push_back(i);
    }
    ld ans = binSearch(0, 1e7, 0);
    valid(ans);
    int g = gcd(A, B);
    cout << A/g << "/" << B/g << endl;
}
