#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
 
int M, MOD;
 
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
 
struct Polynomial {
    modint x;
    modint a;
 
    Polynomial operator+(Polynomial p) const {
        return {p.x + x, p.a + a};
    }
 
    Polynomial operator*(Polynomial p) const {
        return {p.x * a + p.a * x, p.a * a};
    }
 
    Polynomial operator-(Polynomial p) const {
        return {x-p.x, a-p.a};
    }
};
 
int ordering(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*') return 2;
    return 0;
}
 
Polynomial applyOp(Polynomial p1, Polynomial p2, char c) {
    if (c == '+') return p1 + p2;
    if (c == '*') return p1 * p2;
    if (c == '-') return p1 - p2;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int modulo; cin >> modulo;
    cin >> MOD;
    M = MOD;
    stack<char> ops;
    stack<Polynomial> values;
    int i;
 
    for (i = 0; i < s.length(); i++) {
        if (s[i] == ' ')
            continue;
        else if (s[i] == '(') {
            ops.push(s[i]);
        } else if (s[i] >= '0' && s[i] <= '9') {
            int64_t val = 0;
            while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                val *= 10, val += s[i] - '0', val %= MOD, i++;
            }
            values.push({0, val});
            i--;
        } else if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                Polynomial val2 = values.top(); values.pop();
                Polynomial val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        } else if (s[i] == 'x') {
            values.push({1, 0});
        } else {
            while (!ops.empty() && ordering(ops.top()) >= ordering(s[i])) {
                Polynomial val2 = values.top(); values.pop(); 
                Polynomial val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(s[i]);
        }
    }
    while (!ops.empty()) {
        Polynomial val2 = values.top(); values.pop();
        Polynomial val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    for (modint x = 0; x != MOD - 1; x++) {
        if (values.top().a.n + values.top().x * x == modulo) {
            cout << x;
            exit(0);
        }
    }
 
}
