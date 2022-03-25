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

int main() {
    LineContainer lc;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int64_t A, B, C; 
    cin >> A >> B >> C;
    lc.add(0, 0);
    int64_t pref = 0;
    int64_t dp = 0;
    for (int i = 1; i <= N; i++) {
        int64_t x; cin >> x;
        pref += x;
        dp = lc.query(pref) + A * pref * pref + C;
        lc.add(-2 * A * pref,dp + A * pref * pref);
    }
    cout << dp + pref * B;

}
