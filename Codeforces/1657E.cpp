#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
const int M = 998244353;
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
modint binPow(int64_t x, int64_t y) {
    modint ans = 1;
    modint res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
        }
        res *= res, y /= 2;
    }
    return ans;
}
int main () {
    int N, K;
    cin >> N >> K;
    modint combo[N + 1][N + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j == 0) {
                combo[i][j] = 1;
            } else if (i < j) {
                combo[i][j] = 0;
            } else if (i == j) {
                combo[i][j] = 1;
            } else {
                combo[i][j] = combo[i - 1][j] + combo[i - 1][j - 1];
            }
        }
    }
    N--;
    modint dp[N + 1][K + 1];
    for (int k = K; k >= 1; k--) {
        for (int edges = 0; edges <= N; edges++) {
            if (k == K) {
                dp[edges][k] = binPow(K, edges * (edges - 1)/2);
                continue;
            }
            if (edges == 0) {
                dp[edges][k] = 1;
                continue;
            } else if (edges == 1) {
                dp[edges][k] = K - k + 1;
                continue;
            }
            dp[edges][k] = 0;
            for (int e = 0; e <= edges; e++) {
                dp[edges][k] += combo[edges][e] * dp[edges - e][k + 1] * binPow(k, e * (edges - e) + e * (e - 1)/2);
            }
        }
    }
    cout << dp[N][1];
}
