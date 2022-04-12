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
 
const int M = 1e9 + 7;
const int MOD = 1e9 + 7;
using namespace std;
int64_t binPow (int64_t x, int64_t y) {
    int64_t ans = 1, res = x;
    while (y) {
        if (y & 1) ans *= res, ans %= MOD;
        res *= res, res %= MOD, y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
struct modint {
    modint() : n(0) {}
    template <class T> modint(T n) { n %= M; if (n < 0) n += M; this->n = n; }
 
    modint & operator+=(const modint &r) { n += r.n; if (n >= M) n -= M; return *this; }
    modint & operator-=(const modint &r) { n -= r.n; if (n < 0) n += M; return *this; }
    modint & operator*=(const modint &r) { n = (int) ((long long) n * r.n % M); return *this; }
 
    modint & operator--() { if (--n == -1) n = M - 1; return *this; }
    modint & operator++() { if (++n == M) n = 0; return *this; }
    modint operator--(int) { modint t = *this; --*this; return t; }
    modint operator++(int) { modint t = *this; ++*this; return t; }
 
    modint operator-() const { return 0 - *this; }
    modint operator+() const { return *this; }
 
    modint pow(long long k = M - 2) const {
        modint f = *this, p = 1;
        while (k > 0) {
            if (k % 2 == 1) f *= p;
            p *= p, k /= 2;
        }
        return f;
    }
 
    int mod() const { return M; }
 
    friend modint operator+(modint l, const modint &r) { return l += r; }
    friend modint operator-(modint l, const modint &r) { return l -= r; }
    friend modint operator*(modint l, const modint &r) { return l *= r; }
 
    friend bool operator==(const modint &l, const modint &r) { return l.n == r.n; }
    friend bool operator!=(const modint &l, const modint &r) { return l.n != r.n; }
 
    friend ostream & operator<<(ostream &out, const modint &r) { return out << r.n; }
 
    int n;
};
 
vector<pair<int,int>> compress (vector<pair<int,int>> &vec) {
    set<int> s;
    for (auto& p: vec) {
        s.insert(p.first), s.insert(p.second);
    }
    vector<int> v; for (int i: s) v.push_back(i);
    vector<pair<int,int>> grids;
    grids.emplace_back(-1, -1);
    for (int i = 0; i < v.size(); i++) {
        grids.emplace_back(v[i], v[i]);
        if (i + 1 != v.size() && v[i] + 1 <= v[i + 1] - 1) grids.emplace_back(v[i] + 1, v[i + 1] - 1);
    }
    return grids;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    vector<pair<int,int>> points(N);
    for (int i = 0; i < N; i++) cin >> points[i].first >> points[i].second;
    vector<pair<int,int>> grid = compress(points);
    modint combo[grid.size()][N + 1];
    for (int i = 0; i < grid.size(); i++) {
        combo[i][0] = 1;
        for (int j = 1; j <= N; j++) {
            combo[i][j] = combo[i][j - 1] * binPow(j, MOD - 2) * (grid[i].second - grid[i].first + j);
        }
    }
    modint dp[N + 1][grid.size()];
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i < grid.size(); i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j < grid.size(); j++) {
            dp[i][j] = dp[i][j -1];
            int pos = 0;
            for (int k = i; k >= 1; k--) {
                if (grid[j].first >= points[k - 1].first && grid[j].second <= points[k - 1].second) {
                    dp[i][j] += dp[k - 1][j - 1] * combo[j][pos + 1];
                    pos++;
                }
            }
        }
    }
    cout << dp[N][grid.size() - 1] - 1;
}
