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
#define ll long long
#include <map>

using namespace std;
class SparseTableMax {
public:
    vector<vector<int64_t>> dp;
    int64_t query (int l, int r) {
        int sz = log2(r - l + 1);
        return max(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTableMax (vector<int64_t> v) {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize((int)log2((int)v.size()) + 1);
        }
        for (int i = 0; i < v.size(); i++) {
            dp[i][0] = v[i];
        }
        for (int i = 1; i <= (int)log2((int)v.size()); i++) {
            for (int j = 0; j < v.size(); j++) {
                dp[j][i] = max(dp[min(j + (1 << (i - 1)), (int)v.size() - 1)][i - 1], dp[j][i - 1]);
            }
        }
    }
};
class SparseTableMin {
public:
    vector<vector<int64_t>> dp;
    int64_t query (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTableMin (vector<int64_t> v) {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize((int)log2((int)v.size()) + 1);
        }
        for (int i = 0; i < v.size(); i++) {
            dp[i][0] = v[i];
        }
        for (int i = 1; i <= (int)log2((int)v.size()); i++) {
            for (int j = 0; j < v.size(); j++) {
                dp[j][i] = min(dp[min(j + (1 << (i - 1)), (int)v.size() - 1)][i - 1], dp[j][i - 1]);
            }
        }
    }
};
int find_index_of_minimum (int l, int r, SparseTableMin& stm) {
    int L = l;
    int R = r;
    int64_t abs_min = stm.query(l, r);
    while (L != R) {
        int M = (L + R)/2;
        if (stm.query(l, M) == abs_min) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    return L;
}
int find_index_of_maximum (int l, int r, SparseTableMax& stm) {
    int L = l;
    int R = r;
    int64_t abs_min = stm.query(l, r);
    while (L != R) {
        int M = (L + R)/2;
        if (stm.query(l, M) == abs_min) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    assert(L >= l && L <= r);
    return L;
}
bool rec (int l, int r, SparseTableMax &stmax, SparseTableMin &stmin, SparseTableMax &prefmax, SparseTableMin &prefmin) {
    if (l >= r) {
        return true;
    }
    int ind = find_index_of_maximum(l, r, stmax);
    int pref_r = find_index_of_maximum(ind + 1, r + 1, prefmax);
    int pref_l = find_index_of_minimum(l, ind, prefmin);
    if (prefmax.query(pref_r, pref_r) - prefmax.query(pref_l, pref_l) - stmax.query(ind, ind) > 0) {
        return false;
    }
    return rec(l, ind - 1, stmax, stmin, prefmax, prefmin) && rec(ind + 1, r, stmax, stmin, prefmax, prefmin);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> arr(n);
        vector<int64_t> pref;
        pref.push_back(0);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            pref.push_back(pref.back() + arr[i]);
        }
        SparseTableMax stmax(arr);
        SparseTableMin stmin(arr);
        SparseTableMax prefmax(pref);
        SparseTableMin prefmin(pref);
        bool b = rec(0, n - 1, stmax, stmin, prefmax, prefmin) << '\n';
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
}
