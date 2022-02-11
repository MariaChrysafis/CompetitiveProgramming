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
int N;
int M;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    vector<vector<modint>> combo(N + 1);
    vector<modint> fact = {1};
    while (fact.size() != N + 1) {
        fact.push_back(fact.back() * fact.size());
    }
    for (int i = 0; i <= N; i++) {
        combo[i].assign(N + 1, 0);
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (i < j) {
                combo[i][j] = 0;
                continue;
            }
            if (j == 0) {
                combo[i][j] = 1;
                continue;
            }
            combo[i][j] = combo[i - 1][j - 1] + combo[i - 1][j ];
        }
    }
    const int offset = N * (N - 1)/2;
    modint past_dp[N * N + 1], present_dp[N * N + 1];
    modint pref[N * N + 2];
    modint pref1[N * N + 2];
    past_dp[offset] = 1;
    for (int i = 1; i < N * N + 2; i++) {
        pref[i] = pref[i - 1] + past_dp[i - 1];
        pref1[i] = pref1[i - 1] + past_dp[i - 1] * (i - 1);
    }
    modint ans = 0;
    for (int len = N - 3; len >= 0; len--) {
        int n = N - len - 1;
        for (int k = n - 1; k < N * (N - 1) + 1; k++) {
        	present_dp[k] = n * (pref[k + n] - pref[k - n + 1]) + k * (pref[k + n] - pref[k] - pref[k] + pref[k - n + 1]) - pref1[k + n] + pref1[k] + pref1[k] - pref1[k - n + 1];
        }
        for (int k = 0; k < n - 1; k++) {
            present_dp[k] = n * pref[k + n] + k * (pref[k + n] - pref[k] - pref[k]) - pref1[k + n] + pref1[k] + pref1[k];
         }
        pref[0] = pref1[0] = 0;
        for (int i = 1; i < N * N + 2; i++) {
            pref[i] = pref[i - 1] + present_dp[i - 1];
            pref1[i] = pref1[i - 1] + present_dp[i - 1] * (i - 1);
        }
        for (int p = 1; p < N - len; p++) {
            if (offset + 1 + p > N * N + 1 - 1) break;
            ans = ans + (pref[N * N + 1] - pref[offset + 1 + p]) * combo[N][len] * fact[len] * (N - len - p);
        }
        for (int i = 0; i < N * N + 1; i++) {
            swap(past_dp[i], present_dp[i]);
            present_dp[i] = 0;
        }
    }
    cout << ans << '\n';
}
