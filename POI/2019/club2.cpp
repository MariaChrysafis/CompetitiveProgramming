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

using namespace std;
struct SparseTable {
    vector<vector<vector<int>>> dp;
    int N;
    int query (int flag, int l, int r) {
        if (l > r) return 0;
        int sz = log2(r - l + 1);
        int ans = dp[flag][l][sz] | dp[flag][r - (1 << sz) + 1][sz];
        return ans;
    }
    void read (vector<int> arr) {
        dp.resize(2);
        for (int t = 0; t < 2; t++) {
            dp[t].resize(arr.size());
            for (int j = 0; j < arr.size(); j++) {
                dp[t][j].resize(25);
            }
        }
        int tc = 2;
        while (tc--) {
            for (int i = 0; i < arr.size(); i++) {
                arr[i] = (1 << N) - 1 - arr[i];
            }
            for (int j = 0; j < 25; j++) {
                for (int i = 0; i < arr.size(); i++) {
                    if (j == 0) {
                        dp[tc][i][j] = arr[i];
                        continue;
                    }
                    dp[tc][i][j] = dp[tc][i][j - 1] | dp[tc][min(i + (1 << (j - 1)), (int)arr.size() - 1)][j - 1];
                }
            }
        }
    }
};
int N, M;
SparseTable st;
bool justEnough (int l, int r) {
    if (st.query(0, l, r) != st.query(0, 0, M - 1)) {
        return false;
    }
    if (st.query(1, l, r) != st.query(1, 0, M - 1)) {
        return false;
    }
    return true;
}
bool tooMuch (int l, int r) {
    int a = st.query(0, 0, l - 1) | st.query(0, r + 1, M - 1);
    if (a != st.query(0, 0, M - 1)) {
        return false;
    }
    int b = st.query(1, 0, l - 1) | st.query(1, r + 1, M - 1);
    if (b != st.query(1, 0, M - 1)) {
        return false;
    }
    return true;
}
int findFirstValid (int i) {
    int l = i;
    int r = M - 1;
    while (l != r) {
        int m = (l + r)/2;
        if (justEnough(i, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}
int findLastValid (int i) {
    int l = i;
    int r = M - 1;
    while (l != r) {
        int m = (l + r + 1)/2;
        if (tooMuch(i, m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return r;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    st.N = N;
    vector<int> v(M);
    for (int i = 0; i < v.size(); i++) {
        cin >> v[i];
    }
    st.read(v);
    int64_t ans = 0;
    for (int i = 0; i < M; i++) {
        if (!justEnough(i, M - 1)) continue;
        int l = findFirstValid(i);
        int r = findLastValid(i);
        if (r == M - 1) r--;
        ans += max(r - l + 1, 0);
    }
    cout << ans;
    cout << '\n';
}
