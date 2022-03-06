#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
 
using namespace std;
class SparseTable {
public:
    vector<vector<int>> dp;
    vector<int> v;
    int query (int l, int r) {
        if (l == r) {
            return v[l];
        }
        if (l > r) {
            return 0;
        }
        int sz = log2(r - l + 1);
        return dp[l][sz] ^ query(l + (1 << sz), r);
    }
    SparseTable (vector<int> v) {
        this->v = v;
        const int n = v.size();
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(32);
            dp[i][0] = v[i];
        }
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < v.size(); i++) {
                dp[i][j] = dp[min(i + (1 << (j - 1)), n - 1)][j - 1] ^ dp[i][j - 1];
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    SparseTable st(arr);
    while (Q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << st.query(x, y) << '\n';
    }
}
