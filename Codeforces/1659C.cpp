#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <set>
using namespace std;
int cst (string s) {
    int a = 0;
    int b = 0;
    int m = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'A') {
            a++;
            b = 0;
        } else {
            b++;
            a = 0;
        }
        m = max(a, max(b, m));
    }
    return m;
}
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, a, b;
        cin >> n >> a >> b;
        vector<int64_t> arr(n + 1);
        arr[0] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        int64_t suf = 0;
        for (int64_t i: arr) suf += i;
        int64_t myMin = b * suf;
        for (int i = 1; i <= n; i++) {
            suf -= arr[i];
            int64_t cst = a * arr[i] + b * arr[i] - b * arr[i] * (n - i);
            cst += b * suf;
            myMin = min(myMin, cst);
        }
        cout << myMin << '\n';
    }
}
