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
#include <limits.h>
#include <queue>
 
using namespace std;
const int MOD = 10007;
class Node {
public:
    int dp[21]; //how many ways such that exactly C people get a painting
    bool id;
    Node (bool id) {
        this->id = id;
        for (int i = 0; i < 21; i++) {
            dp[i] = 0;
        }
    }
};
Node merge (Node n1, Node n2) {
    if (!n1.id) return n2;
    if (!n2.id) return n1;
    Node ans(true);
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            ans.dp[min(i + j, 20)] += (n1.dp[j] * n2.dp[i]) % MOD;
        }
    }
    for (int i = 0; i < 21; i++) {
        ans.dp[i] %= MOD;
    }
    return ans;
}
Node get_node (pair<int,int> p) {
    Node ans(true);
    ans.dp[0] = p.second;
    ans.dp[1] = p.first;
    return ans;
}
template<class T>
class SegmentTree {
public:
 
    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, Node(false));
    }
 
    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }
 
    vector<T> val;
private:
    int N;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, C;
    cin >> N >> C;
    SegmentTree<Node> st(N);
    vector<int> x(N), y(N);
    for (int i = 0; i < N; i++) cin >> x[i];
    for (int i = 0; i < N; i++) cin >> y[i];
    for (int i = 0; i < N; i++) {
        x[i] %= MOD, y[i] %= MOD;
        st.update(i, get_node({x[i], y[i]}));
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int ind, a, b;
        cin >> ind >> a >> b;
        a %= MOD, b %= MOD;
        ind--;
        st.update(ind, get_node({a, b}));
        int64_t ans = 0;
        for (int i = C; i <= 20; i++) {
            ans += st.val[0].dp[i];
        }
        cout << ans % MOD << '\n';
    }
}
