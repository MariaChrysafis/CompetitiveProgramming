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
struct Line {
    mutable int64_t k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(int64_t x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    //Container where you can add lines of the form kx+m, and query maximum values at points x.
    //https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
    static const int64_t inf = LLONG_MAX;
    int64_t div(int64_t a, int64_t b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(int64_t k, int64_t m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    int64_t query(int64_t x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

int main() {
    LineContainer lc;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    vector<pair<pair<int64_t,int64_t>,int64_t>> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i].first.first >> arr[i].first.second >> arr[i].second;
    }
    sort(arr.begin(), arr.end());
    vector<int64_t> dp(N + 1);
    dp[0] = 0;
    int64_t myMax = 0;
    lc.add(0, 0);
    for (int i = 1; i <= N; i++) {
        dp[i] = lc.query(arr[i - 1].first.second);
        assert(dp[i] >= 0);
        dp[i] +=  arr[i - 1].first.first * arr[i - 1].first.second - arr[i - 1].second;
        lc.add(-arr[i - 1].first.first, dp[i]);
        myMax = max(myMax, dp[i]);
    }
    cout << myMax;

}
