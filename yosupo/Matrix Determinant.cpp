#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
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
template <typename T>
class Matrix {
public:
    vector<vector<T>> vec;
    int N, M;
    void print () {
        for (int i = 0; i < vec.size(); i++) {
            for (int j = 0; j < vec[0].size(); j++) {
                cout << vec[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    void set (int i, int j, T x) {
        vec[i][j] = x;
    }
    void add (int i, int j, T x) {
        vec[i][j] += x;
    }
    T get (int i, int j) {
        return vec[i][j];
    }
    Matrix (int N, int M) {
        this->N = N, this->M = M, vec.resize(N); for (int i = 0; i < N; i++) vec[i].resize(M);
    }
    Matrix (vector<vector<T>> v) {
        this->N = (int)v.size(), this->M = (int)v[0].size(), this->vec = v;
    }
    Matrix operator* (Matrix& m1) {
        assert(this->M == m1.N);
        Matrix ans(this->N, m1.M);
        for (int i = 0; i < this->N; i++) {
            for (int j = 0; j < m1.M; j++) {
                ans.set(i, j, 0);
                for (int k = 0; k < this->M; k++) {
                    ans.add(i, j, this->get(i, k) * m1.get(k, j));
                }
            }
        }
        return ans;
    }
    bool sgn = false;
    Matrix upper_triangular () {
        Matrix m(vec);
        for (int i = this->M - 1; i >= 1; i--) {
            for (int j = 0; j < i; j++) {
                if (m.get(i, j + 1) != 0) {
                    T dif = m.get(i, j)/m.get(i, j + 1);
                    for (int k = 0; k < this->M; k++) {
                        m.vec[k][j] = -m.vec[k][j + 1] * dif + m.vec[k][j];
                    }
                } else {
                    for (int k = 0; k < this->M; k++) {
                        swap(m.vec[k][j], m.vec[k][j + 1]);
                    }
                    sgn = !sgn;
                }
            }
        }
        return m;
    }
    T determinant () {
        sgn = false;
        Matrix m = upper_triangular();
        T ans = 1;
        for (int i = 0; i < m.M; i++) {
            ans *= m.get(i, i);
        }
        if (sgn) ans *= -1;
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    Matrix<modint> m1(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            modint x; cin >> x.n;
            m1.set(i, j, x);
        }
    }
    cout << m1.determinant();
}
