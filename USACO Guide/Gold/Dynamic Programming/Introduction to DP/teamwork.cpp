#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
#define ll int
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return max(a,b); }
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
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    Seg<int> st;
    vector<int> teams(N);
    st.init(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> teams[i];
        st.upd(i, teams[i]);
    }
    ll dp[N + 1];
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        if (i <= K) {
            dp[i] = st.query(0, i - 1) * i;
            continue;
        }
        dp[i] = 0;
        for (int len = 1; len <= K; len++) {
            dp[i] = max(dp[i - len] + st.query(i - len, i - 1) * len, dp[i]);
        }
    }
    cout << dp[N] << endl;
}
