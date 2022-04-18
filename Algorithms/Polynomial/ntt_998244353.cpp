//https://judge.yosupo.jp/submission/86590

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
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

vector<modint> fastFourierTransform(vector<modint> a, modint w) {
    if ((int)a.size() == 1) {
        return {a[0]};
    }
    vector<modint> a1, a2;
    for (int i = 0; i < a.size(); i += 2) {
        a1.push_back(a[i]);
    }
    for (int i = 1; i < a.size(); i += 2) {
        a2.push_back(a[i]);
    }
    vector<modint> v1 = fastFourierTransform(a1, w * w);
    vector<modint> v2 = fastFourierTransform(a2, w * w);
    assert(v1.size() == v2.size());
    vector<modint> res(a.size());
    modint w0 = 1;
    for (int i = 0; i < a.size()/2; i++) {
        res[i] = v1[i] + v2[i] * w0;
        w0 *= w;
    }
    w0 = 1;
    for (int i = a.size()/2; i < a.size(); i++) {
        res[i] = v1[i - a.size()/2] - v2[i - a.size()/2] * w0;
        w0 *= w;
    }
    return res;
}
modint binPow (modint x, int y) {
    modint res = x;
    modint ans = 1;
    while (y > 0) {
        if (y & 1) ans *= res;
        res *= res, y /= 2;
    }
    return ans;
}
const double pi = acos(-1);
vector<modint> eval (vector<modint> a) {
    while (__builtin_popcount(a.size()) != 1) {
        a.push_back(0);
    }
    return fastFourierTransform(a,binPow(3, (MOD - 1)/(int)a.size()));
}
vector<modint> interpolate (vector<modint> v) {
    int n = v.size();
    vector<modint> inv = fastFourierTransform(v, binPow(3, MOD - 1 - (MOD - 1)/(int)v.size()));
    for (int i = 0; i < n; i++) {
        inv[i] = inv[i]/n;
    }
    return inv;
}
vector<modint> multiply (vector<modint> a, vector<modint> b) {
    if (a.size() > b.size()) swap(a, b);
    while (a.size() != b.size()) a.emplace_back(0);
    while (__builtin_popcount(a.size()) != 1) a.emplace_back(0);
    while (__builtin_popcount(b.size()) != 1) b.emplace_back(0);
    while (a.size() != 2 * b.size()) {
        a.emplace_back(0);
    }
    vector<modint> v1 = eval(a);
    while (a.size() != b.size()) {
        a.pop_back();
    }
    while (b.size() != 2 * a.size()) {
        b.emplace_back(0);
    }
    vector<modint> v2 = eval(b);
    while (a.size() != b.size()) {
        b.pop_back();
    }
    for (int i = 0; i < v1.size(); i++) {
        v1[i] *= v2[i];
    }
    return interpolate(v1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N1, N2;
    cin >> N1 >> N2;
    vector<modint> v1(N1), v2(N2);
    for (int i = 0; i < N1; i++)
        cin >> v1[i].n;
    for (int i = 0; i < N2; i++)
        cin >> v2[i].n;
    cout << '\n';
    vector<modint> res = multiply(v1, v2);
    while (res.size() != N1 + N2 - 1) {
        res.pop_back();
    }
    for (modint i: res) {
        cout << i << ' ';
    }
    cout << '\n';
}
