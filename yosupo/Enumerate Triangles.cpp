#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <set>
using namespace std;
const int MOD = 998244353;
struct modint {
    modint() : n(0) {}
    template <class T> modint(T n) { n %= MOD; if (n < 0) n += MOD; this->n = n; }

    modint & operator+=(const modint &r) { n += r.n; if (n >= MOD) n -= MOD; return *this; }
    modint & operator-=(const modint &r) { n -= r.n; if (n < 0) n += MOD; return *this; }
    modint & operator*=(const modint &r) { n = (int) ((long long) n * r.n % MOD); return *this; }

    modint & operator--() { if (--n == -1) n = MOD - 1; return *this; }
    modint & operator++() { if (++n == MOD) n = 0; return *this; }
    modint operator--(int) { modint t = *this; --*this; return t; }
    modint operator++(int) { modint t = *this; ++*this; return t; }

    modint operator-() const { return 0 - *this; }
    modint operator+() const { return *this; }

    modint pow(long long k = MOD - 2) const {
        modint f = *this, p = 1;
        while (k > 0) {
            if (k % 2 == 1) f *= p;
            p *= p, k /= 2;
        }
        return f;
    }

    int mod() const { return MOD; }

    friend modint operator+(modint l, const modint &r) { return l += r; }
    friend modint operator-(modint l, const modint &r) { return l -= r; }
    friend modint operator*(modint l, const modint &r) { return l *= r; }
    friend modint operator/(modint l, const modint &r) {
        modint f = l, p = r; long long k = MOD - 2;
        while (k > 0) {
            if (k % 2 == 1) f *= p;
            p *= p, k /= 2;
        }
        return f;
    }
    friend bool operator==(const modint &l, const modint &r) { return l.n == r.n; }
    friend bool operator!=(const modint &l, const modint &r) { return l.n != r.n; }

    friend ostream & operator<<(ostream &out, const modint &r) { return out << r.n; }

    int n;
};
class Graph {
public:
    vector<set<int>> adj;
    vector<modint> val;
    Graph(int n) {
        adj.resize(n), val.resize(n);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < n; i++) cin >> g.val[i].n;
    vector<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edges.emplace_back(u, v);
        g.adj[u].insert(v), g.adj[v].insert(u);
    }
    modint ans = 0;
    for (auto& p: edges) {
        if (g.adj[p.first].size() > g.adj[p.second].size()) {
            swap(p.first, p.second);
        }
        for (int i: g.adj[p.first]) {
            if (g.adj[p.second].count(i)) {
                ans += g.val[i] * g.val[p.first] * g.val[p.second];
            }
        }
    }
    cout << ans/3;
}
