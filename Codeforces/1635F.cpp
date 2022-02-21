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
class segmentTree {
public:
    vector<int64_t> v;
    vector<int64_t> val;

    int64_t ID = LLONG_MAX;

    int64_t op(int64_t a, int64_t b) {
        return min(a,b);
    }
    int64_t query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    int64_t query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, int64_t y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    segmentTree (int n) {
        v.assign((1 << (int) ceil(log2(n))), ID);
        val.assign(v.size() * 2, ID);
    }

};

class SparseTable {
    vector<vector<int64_t>> dp;
    vector<int64_t> arr;
public:
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTable (vector<int64_t> v) {
        this->arr = v;
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(20);
            dp[i][0] = arr[i];
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < dp.size(); i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)dp.size() - 1)][j - 1]);
            }
        }
    }
};

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<vector<pair<int,int>>> queries(N);
    vector<pair<int64_t,int64_t>> points(N);
    vector<int64_t> w;
    for (int i = 0; i < N; i++) {
        cin >> points[i].first >> points[i].second;
        w.push_back(points[i].second);
    }
    SparseTable st(w);
    for (int q = 0; q < Q; q++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[l].push_back({r, q});
    }
    vector<vector<int>> intervals(N);
    for (int i = 0; i < N; i++) {
        if (i != 0 && st.query(0, i - 1) <= w[i]) {
            int l = 0;
            int r = i - 1;
            while (l != r) {
                int mid = (l + r + 1) / 2;
                if (st.query(mid, i - 1) <= w[i]) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            intervals[l].push_back(i);
        }
        if (i != N - 1 && st.query(i + 1, N - 1) <= w[i]) {
            int l = i + 1;
            int r = N - 1;
            while (l != r) {
                int mid = (l + r) / 2;
                if (st.query(i + 1, mid) <= w[i]) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            intervals[i].push_back(l);
        }
    }
    segmentTree seg(N);
    int64_t a[Q];
    vector<int64_t> arr;
    arr.assign(N, LLONG_MAX);
    for (int l = N - 1; l >= 0; l--) {
        for (int r: intervals[l]) {
            int64_t cost = (points[r].first - points[l].first) * (points[l].second + points[r].second);
            if (cost < arr[r]) {
                seg.update(r, (arr[r] = cost));
            }
        }
        for (auto& p: queries[l]) {
            a[p.second] = seg.query(l, p.first);
        }
    }
    for (int64_t i: a) {
        cout << i << '\n';
    }
}
