#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] += y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int arr[n];
        SegmentTree<int> st(n + 1);
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            ans += st.query(arr[i], n);
            st.update(arr[i], 1);
        }
        cout << ans << '\n';
    }
}
