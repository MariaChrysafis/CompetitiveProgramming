#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
const int MOD = 1e9;
struct Node {
    int64_t left;
    int64_t right;
    int64_t mid;
    int64_t sum;
};
Node merge (Node a, Node b) {
    Node c;
    c.sum = a.sum + b.sum;
    c.mid = max(max(a.mid, b.mid), a.right + b.left);
    c.left = max(a.left, a.sum + b.left);
    c.right = max(b.right, b.sum + a.right);
    return c;
}
Node get_node (int x) {
    Node c;
    c.left = c.right = c.mid = max(x, 0);
    c.sum = x;
    return c;
}
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = get_node(0); T comb(T a, T b) { return merge(a,b); }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Seg<Node> st;
    int N, M; cin >> N >> M;
    st.init(N + 1);
    for (int i = 0; i < N; i++) {
        int64_t x; cin >> x;
        st.upd(i, get_node(x));
    }
    //cout << st.query(0, N - 1).mid << '\n';
    while (M--) {
        int64_t k, x;
        cin >> k >> x;
        k--;
        st.upd(k, get_node(x));
        cout << st.query(0, N - 1).mid << '\n';
    }
 
}
