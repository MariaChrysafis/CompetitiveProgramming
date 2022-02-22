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
modint binPow (modint x, int y) {
    modint ans = 1;
    modint res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
        }
        y /= 2;
        res *= res;
    }
    return ans;
}

modint inv (modint x) {
    return binPow(x, M - 2);
}

vector<modint> fact;

modint combo (int x, int y) {
    return fact[x] * inv(fact[y] * fact[x - y]);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact = {1};
    while (fact.size() != 2e7) {
        fact.push_back(fact.back() * fact.size());
    }
    int N, X, Y, Z;
    cin >> N >> X >> Y >> Z;
    X = abs(X), Y = abs(Y), Z = abs(Z);
    modint ans = 0;
    if (N % 2 != (X + Y + Z) % 2) {
        cout << 0;
        exit(0);
    }
    const int m = (N - (X + Y + Z))/2;
    for (int a = 0; a <= m; a++) {
        ans += combo(N, Z + 2 * (m - a)) * combo (Z + 2 * (m - a), m - a) * combo(X + Y + 2 * a, a) * combo(X + Y + 2 * a, X + a);
    }
    cout << ans;
}
