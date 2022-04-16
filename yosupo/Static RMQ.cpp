#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <set>
using namespace std;
class SparseTable {
public:
    vector<vector<int>> dp;
    int query (int l, int r) {
        int lg2 = log2(r - l + 1);
        return min(dp[l][lg2], dp[r - (1 << lg2) + 1][lg2]);
    }
    SparseTable (vector<int> v) {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(log2(v.size()) + 1);
            dp[i][0] = v[i];
        }
        for (int j = 0; j <= log2(v.size()); j++) {
            for (int i = 0; i + (1 << (j - 1)) < v.size(); i++) {
                dp[i][j] = min(dp[i + (1 << (j -1 ))][j - 1], dp[i][j - 1]);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    SparseTable st(v);
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r - 1) << '\n';
    }
}
