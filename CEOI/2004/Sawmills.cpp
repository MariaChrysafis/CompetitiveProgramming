#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>

using namespace std;

inline namespace _LineContainer { //Line Container copied from USACO Guide
    bool _Line_Comp_State;
    struct Line {
        // k is slope, m is intercept, p is intersection point
        mutable long long k, m, p;
        bool operator<(const Line& o) const {
            return _Line_Comp_State ? p < o.p : k < o.k;
        }
    };

    struct LineContainer : multiset<Line> {
        long long div(long long a, long long b) { return a / b - ((a ^ b) < 0 && a % b); }

        bool isect(iterator x, iterator y) {
            if (y == end()) {
                x->p = LLONG_MAX;
                return false;
            }
            if (x->k == y->k)
                x->p = x->m > y->m ? LLONG_MAX : -LLONG_MAX;
            else
                x->p = div(y->m - x->m, x->k - y->k);
            return x->p >= y->p;
        }

        void add(long long k, long long m) {
            auto z = insert({k, m, 0}), y = z++, x = y;
            while (isect(y, z))
                z = erase(z);
            if (x != begin() && isect(--x, y))
                isect(x, y = erase(y));
            while ((y = x) != begin() && (--x)->p >= y->p)
                isect(x, erase(y));
        }

        long long query(long long x) {
            assert(!empty());
            _Line_Comp_State = 1;
            auto l = *lower_bound({0,0,x});
            _Line_Comp_State = 0;
            return l.k * x + l.m;
        }
    };
}
vector<int64_t> w, d;
int64_t get_weight (int x, int y) {
    return w[y + 1] - w[x];
}
int64_t get_distance (int x, int y) {
    return d[y + 1] - d[x];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    w.resize(N + 1), d.resize(N + 1);
    w[0] = d[0] = 0;
    vector<int> weight, distance;
    for (int i = 0; i < N; i++) {
        int64_t W, D; cin >> W >> D; weight.push_back(W), distance.push_back(D);
        w[i + 1] = w[i] + W;
        d[i + 1] = d[i] + D;
    }
    int64_t T = 0;
    for (int i = 0; i < N; i++) {
        T += get_distance(i, N - 1) * get_weight(i, i);
    }
    int64_t ans = T;
    LineContainer lc;
    lc.add(0, 0);
    for (int b = 1; b < N; b++) {
        ans = min(ans, T - (d[N] - d[b]) * w[b + 1] - lc.query(d[b])), lc.add(w[b + 1], -d[b] * w[b + 1]);
    }
    if (N == 2) {
        ans = 0;
    }
    cout << ans << '\n';

}
