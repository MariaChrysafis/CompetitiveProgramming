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
 
using namespace std;
 
class Node {
public:
    int64_t dp[2][2] = {{-(long long)1e18, -(long long)1e18}, {-(long long)1e18, -(long long)1e18}};
    int64_t left;
    int64_t right;
    bool okay = true;
};
 
Node merge (Node x, Node y) {
    if (!x.okay) {
        return y;
    }
    if (!y.okay) {
        return x;
    }
    Node ans;
    ans.left = x.left;
    ans.right = y.right;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][1] + y.dp[1][j]);
            ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][0] + y.dp[1][j]);
            ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][1] + y.dp[0][j]);
            ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][0] + y.dp[0][j]);
            if (x.right <= y.left) ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][0] + abs(x.right - y.left) + y.dp[0][j]);
            else ans.dp[i][j] = max(ans.dp[i][j], x.dp[i][1] + abs(x.right - y.left) + y.dp[1][j]);
        }
    }
    return ans;
}
 
void update(Node &x, int64_t val) {
    x.left += val, x.right += val;
}
 
Node INF;
 
struct segmentTree {
    vector<Node> vec;
    vector<int64_t> addLater;
 
    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        update(vec[2 * v + 1], addLater[v]);
        update(vec[2 * v], addLater[v]);
        addLater[v] = 0;
    }
 
    void upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            update(vec[dum], val);
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }
 
    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }
 
    Node get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return merge(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }
 
    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }
 
    vector<int> arr;
 
    void init (int dum, int tl, int tr) {
        if (tl == tr) {
            vec[dum].dp[0][0] = vec[dum].dp[1][1] = 0;
            vec[dum].left = vec[dum].right = arr[tr];
            return;
        }
        int mid = (tl + tr) >> 1;
        init(2 * dum, tl, mid);
        init(2 * dum + 1, mid + 1, tr);
        vec[dum] = merge(vec[2 * dum], vec[2 * dum + 1]);
    }
 
    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, INF);
        addLater.resize(sz * 2);
        arr.resize(sz);
    }
 
    void build () {
        init(1, 0, (int)vec.size()/2 - 1);
    }
 
};
segmentTree st;
int N;
 
int main() {
    //freopen("inp.txt", "r", stdin);
    //freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int D;
    cin >> N >> D;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        cin >> st.arr[i];
    }
    INF.okay = false;
    st.build();
    st.upd(0, 0, 0);
    while (D--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        st.upd(l, r, x);
        cout << max(max(st.get(0, N - 1).dp[1][1], st.get(0, N - 1).dp[1][0]), max(st.get(0, N - 1).dp[0][1], st.get(0, N - 1).dp[0][0])) << '\n';
    }
}
