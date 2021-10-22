#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <vector>
#include <map>
using namespace std;
#define ll long long
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
Seg<ll> st;
vector<ll> pref;
int cost (int l, int r) {
    return st.query(l, r) * (r - l + 1) - (pref[r + 1] - pref[l]);
}
int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    st.init(N + 2);
    vector<ll> v(N);
    pref = {0};
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        st.upd(i, v[i]);
        pref.push_back(pref.back() + v[i]);
    }
    ll dp[N + 1][K + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int k = 0; k <= K; k++) {
            if (k == 0) {
                dp[i][k] = cost(0, i - 1);
            } else {
                for (int j = 0; j < i; j++) {
                    dp[i][k] = min(dp[i][k], dp[j][k - 1] + cost(j, i - 1));
                }
            }
        }
    }
    cout << dp[N][K] << endl;
}
