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
#include <unordered_map>

using namespace std;

struct BIT {
    vector<int> bit;

    int pref(int ind) {
        int ans = 0;
        ind++;
        while (ind > 0) {
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }

    int sum(int l, int r) {
        if (l == 0) {
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }

    void update(int ind, int val) {
        ind++;
        while (ind < bit.size()) {
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }

    void construct(int n) {
        bit.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            bit[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            update(i, 0);
        }
    }
};

struct MinMaxLazyST {
    vector<int> tree;
    vector<int> lazy;
    int N;
    int NONE;

    MinMaxLazyST(int n) {
        N = n;
        NONE = 1e9;
        tree.assign(4 * N + 1, 0LL);
        lazy.assign(4 * N + 1, 0LL);
    }

    void add(int L, int R, int val) {
        add(0, 0, N - 1, L, R, val);
    }

    void add(int n, int L, int R, int uL, int uR, int val) {
        push(n, L, R);
        if (uL <= L && R <= uR) {
            lazy[n] += val;
            push(n, L, R);
            return;
        } else if (L > uR || R < uL || L == R) {
            return;
        }
        add(2 * n + 1, L, (L + R) / 2, uL, uR, val);
        add(2 * n + 2, (L + R) / 2 + 1, R, uL, uR, val);
        tree[n] = min(tree[2 * n + 1], tree[2 * n + 2]);
    }

    long long query(int L, int R) {
        return query(0, 0, N - 1, L, R);
    }

    long long query(int n, int L, int R, int Lq, int Rq) {
        push(n, L, R);
        if (Lq <= L && R <= Rq) {
            return tree[n];
        } else if (R < Lq || Rq < L) {
            return NONE;
        } else {
            return min(query(2 * n + 1, L, (L + R) / 2, Lq, Rq), query(2 * n + 2, (L + R) / 2 + 1, R, Lq, Rq));
        }
    }

    void push(int n, int L, int R) {
        tree[n] += lazy[n];

        if (L < R) {
            lazy[2 * n + 1] += lazy[n];
            lazy[2 * n + 2] += lazy[n];
        }
        lazy[n] = 0LL;
    }

};

void compress(vector<int> &a, vector<int> &b) {
    vector<int> tot;
    for (auto& i: a) tot.push_back(i);
    for (auto& i: b) tot.push_back(i);
    sort(tot.begin(), tot.end());
    unordered_map<int, int> myMap;
    myMap.reserve(100);
    int cntr = 0;
    for (int i: tot) {
        myMap[i] = ++cntr;
    }
    for (int i = 0; i < a.size(); i++) {
        a[i] = myMap[a[i]];
    }
    for (int i = 0; i < b.size(); i++) {
        b[i] = myMap[b[i]];
    }
}

int get_max(vector<int> v) {
    int myMax = 0;
    for (auto& i: v) {
        myMax = max(myMax, i);
    }
    return myMax;
}

int64_t cnt_inversions(vector<int> &v) {
    int n = v.size();
    vector<bool> oc;
    oc.assign(get_max(v) + 1, false);
    for (auto& i: v) {
        oc[i] = true;
    }
    int myMap[oc.size()];
    int cntr = 0;
    for (int i = 0; i < oc.size(); i++) {
        if (oc[i]) {
            myMap[i] = cntr++;
        }
    }
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
    }
    BIT st;
    st.construct(n + 4);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans += st.sum(v[i] + 1, n + 2);
        st.update(v[i], 1);
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<int>> oc_a(n + m + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    compress(a, b);
    for (int i = 0; i < a.size(); i++) {
        oc_a[a[i]].push_back(i);
    }
    MinMaxLazyST st(n + 1);
    for (int i = 0; i <= n; i++) {
        st.add(i, i, i);
    }
    vector<int> oc_b(n + m + 1);
    for (auto& i: b) {
        oc_b[i]++;
    }
    int64_t res = 0;
    for (int i = 1; i <= n + m; i++) {
        for (auto &j: oc_a[i - 1]) {
            st.add(0, j, 1);
        }
        for (auto &j: oc_a[i]) {
            st.add(j + 1, n, -1);
        }
        res += oc_b[i] * st.query(0, n);
    }
    cout << res + cnt_inversions(a) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
