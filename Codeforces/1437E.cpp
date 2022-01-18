#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef int64_t ll;

template<class T>
struct Seg { 
    const T ID = 0;

    T comb(T a, T b) { return max(a, b); }

    int n;
    vector<T> seg;

    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }

    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }

    void upd(int p, T val) { // set val at position p
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }

    T query(int l, int r) {    // sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};

int lis(vector<int> v) {
    int n = v.size();
    //compressing our vector into something such that all elements are in the range [0, v.size() - 1]
    vector<pair<int, int>> vec;
    for (int i = 0; i < v.size(); i++) {
        vec.push_back({v[i], i});
    }
    sort(vec.begin(), vec.end());
    v.clear();
    v.resize(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        v[vec[i].second] = i;
    }
    Seg<int> st;
    st.init(n + 1);
    for (int i = 0; i < n; i++) {
        st.upd(v[i], st.query(0, v[i] - 1) + 1);
    }
    return st.query(0, n);
}

vector<int> extract(vector<int> &v, int l, int r) {
    vector<int> vec;
    for (int i = l; i <= r; i++) {
        vec.push_back(v[i]);
    }
    return vec;
}

int f(vector<int> v, int lower, int upper) {
    if (lower > upper) {
        cout << "-1\n";
        exit(0);
    }
    vector<int> vec;
    for (int i: v) {
        if (i >= lower && i <= upper) {
            vec.push_back(i);
        }
    }
    return v.size() - lis(vec);
}

struct Interval {
    int left_index, right_index;
    int left_value, right_value;
};

const int INF = 1e9;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    for (int i = 0; i < v.size(); i++) {
        cin >> v[i];
        v[i] -= i;
    }
    vector<int> forbidden_indices(K);
    vector<int> val;
    for (int i = 0; i < K; i++) {
        cin >> forbidden_indices[i];
        forbidden_indices[i]--;
        val.push_back(v[forbidden_indices[i]]);
    }
    if (lis(val) != val.size()) {
        cout << "-1\n";
        return 0;
    }
    if (K == 0) {
        cout << v.size() - lis(v);
        return 0;
    }
    vector<Interval> intervals;
    for (int i = 0; i <= K; i++) {
        if (i == 0) {
            intervals.push_back({0, forbidden_indices[i] - 1, -INF, v[forbidden_indices[i]]});
        } else if (i < K) {
            intervals.push_back({forbidden_indices[i - 1] + 1, forbidden_indices[i] - 1, v[forbidden_indices[i - 1]],
                                 v[forbidden_indices[i]]});
        } else {
            intervals.push_back({forbidden_indices.back() + 1, N - 1, v[forbidden_indices.back()], INF});
        }
        if (intervals.back().left_index > intervals.back().right_index) {
            intervals.pop_back();
            continue;
        };
    }
    int ans = 0;
    for (auto &p: intervals) {
        vector<int> res = extract(v, p.left_index, p.right_index);
        ans += f(res, p.left_value, p.right_value);
    }
    cout << ans;
}
