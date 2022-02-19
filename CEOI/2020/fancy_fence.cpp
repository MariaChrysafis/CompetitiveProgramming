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
#include <stack>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;

int M = 1e9 + 7;

struct modint {
    modint() : n(0) {}

    template<class T>
    modint(T n) {
        n %= M;
        if (n < 0) n += M;
        this->n = n;
    }

    modint &operator+=(const modint &r) {
        n += r.n;
        if (n >= M) n -= M;
        return *this;
    }

    modint &operator-=(const modint &r) {
        n -= r.n;
        if (n < 0) n += M;
        return *this;
    }

    modint &operator*=(const modint &r) {
        n = (int) ((long long) n * r.n % M);
        return *this;
    }

    modint &operator--() {
        if (--n == -1) n = M - 1;
        return *this;
    }

    modint &operator++() {
        if (++n == M) n = 0;
        return *this;
    }

    modint operator--(int) {
        modint t = *this;
        --*this;
        return t;
    }

    modint operator++(int) {
        modint t = *this;
        ++*this;
        return t;
    }

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

    friend ostream &operator<<(ostream &out, const modint &r) { return out << r.n; }

    int n;
};
modint c2 (modint x) {
    int64_t n = x.n;
    return (n * (n + 1)/2) % M;
}
const int MOD = 1e9 + 7;

struct SparseTable {
    vector<modint> val;
    vector<vector<int>> dp;
    int query (int l, int r) {
        if (l > r) {
            return INT_MAX;
        }
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[min(r - (1 << sz) + 1, (int)dp.size() - 1)][sz]);
    }
    void init () {
        dp.resize(val.size());
        for (int i = 0; i < dp.size(); i++) {
            dp[i].resize(32);
            dp[i][0] = val[i].n;
        }
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < dp.size(); i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)dp.size() - 1)][j - 1]);
            }
        }
    }
    SparseTable (vector<modint> val) {
        this->val = val;
        init();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<modint> h(N), w(N);
    vector<pair<modint, modint>> grid(N);
    map<int,vector<int>> myMap;
    for (int i = 0; i < N; i++) {
        cin >> h[i].n;
        myMap[h[i].n].push_back(i);
    }
    vector<modint> pref = {0};
    for (int i = 0; i < N; i++) {
        cin >> w[i].n;
        pref.push_back(pref.back() + w[i]);
    }
    for (int i = 0; i < N; i++) {
        grid[i] = make_pair(w[i], h[i]);
    }
    SparseTable st(h);
    modint ans = 0;
    for (auto& p: myMap) {
        int x = p.first;
        for (int i: p.second) {
            if (h[i] == x) {
                int L = 0;
                int R = i;
                while (L != R) {
                    int MID = (L + R)/2;
                    if (st.query(MID, i - 1) >= x) {
                        R = MID;
                    } else {
                        L = MID + 1;
                    }
                }
                int l = L;
                L = i;
                R = N - 1;
                while (L != R) {
                    int MID = (L + R + 1)/2;
                    if (st.query(i + 1, MID) > x) {
                        L = MID;
                    } else {
                        R = MID - 1;
                    }
                }
                int r = R;
                modint sum = (pref[i] - pref[l]) * (pref[r + 1] - pref[i + 1]);
                sum += (pref[r + 1] - pref[l] - w[i]) * w[i];
                ans += sum* c2(x);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        ans += c2(grid[i].first) * c2(grid[i].second);
    }
    cout << ans << '\n';
    return 0;
}
