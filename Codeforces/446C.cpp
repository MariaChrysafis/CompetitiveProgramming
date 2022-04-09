#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>


using namespace std;
const int M = 1000000009;


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

    int64_t n;
};
struct segmentTree {
public:
    vector<modint> addLater;
    vector<modint> vec;
    vector<modint> powr;
    vector<modint> pref;
    void push (int dum, int tl, int tr) {
        addLater[2 * dum + 1] += addLater[dum];
        vec[2 * dum + 1] += addLater[dum] * pref[(tl + tr)/2 - tl + 1];
        addLater[dum] *= powr[(tl + tr)/2 - tl + 1];
        addLater[2 * dum + 2] += addLater[dum];
        vec[2 * dum + 2] += addLater[dum] * pref[tr - (tl + tr)/2];
        addLater[dum] = 0;
    }

    void update (int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) return;
        if (tl >= l && tr <= r) {
            addLater[dum] += powr[tl - l];
            vec[dum] += powr[tl - l] * pref[tr - tl + 1];
            return;
        }
        push(dum, tl, tr);
        update(2 * dum + 1, tl, (tl + tr)/2, l, r);
        update(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r);
        vec[dum] = vec[2 * dum + 1] + vec[2 * dum + 2];
    }

    void update (int l, int r) {
        update(0, 0, (int)vec.size()/2 - 1, l, r);
    }

    modint query (int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) return 0;
        if (tl >= l && tr <= r) return vec[dum];
        push(dum, tl, tr);
        return query(2 * dum + 1, tl, (tl + tr)/2, l, r) + query(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r);
    }
    modint query (int l, int r) {
        return query(0, 0, (int)vec.size()/2 - 1, l, r);
    }

    void resz (int n, modint x) {
        n = (1 << ((int)log2(n) + 1)) * 2;
        vec.assign(n, 0), addLater.assign(n, 0);
        powr = {1}, pref = {0};
        for (int i = 0; i <= n + 1; i++) {
            pref.push_back(pref.back() + powr.back());
            powr.push_back(powr.back() * x);
        }

    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    segmentTree st1, st2;
    modint a = 691504013;
    modint b = 308495997;
    st1.resz(N + 2, a), st2.resz(N + 2, b);
    modint inv = 276601605;
    vector<modint> arr(N + 1);
    vector<modint> pref(N + 1);
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i].n;
        pref[i + 1] = pref[i] + arr[i];
    }
    pref.push_back(pref.back());
    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            st1.update(l - 1, r), st2.update(l - 1, r);
        } else {
            cout << (st1.query(l, r) - st2.query(l, r)) * inv + pref[r] - pref[l - 1] << '\n';
        }
    }
}
