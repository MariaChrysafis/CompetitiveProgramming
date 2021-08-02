#include <iostream>
#include <vector>
#include <cmath>
#include <set>
 
#define ll long long
using namespace std;
 
void print(vector<int> v) {
    for (int i: v) cout << i << " ";
    cout << endl;
}
 
template<class T>
struct Seg { // comb(ID,b) = b
    const T ID = 0;
 
    T comb(T a, T b) {
        return a + b;
    }
 
    int n;
    vector<T> seg;
 
    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
 
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
 
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
 
    T query(int l, int r) {    // min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};
 
const int MAX = 6e5;
 
int ceil(int a, int b) {
    return a / b + (a % b != 0);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> v(n), pref(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        pref[i + 1] = pref[i] + v[i];
    }
    Seg<ll> st1;
    Seg<ll> st2;
    vector<ll> Q(n);
    vector<ll> P(n);
    st1.init(MAX + 10), st2.init(MAX + 10);
    for (int i = 0; i < MAX + 9; i++) {
        st1.upd(i, 0), st2.upd(i, 0);
    }
    st1.upd(v[0], 1);
    Q[0] = 0;
    for (int i = 1; i < n; i++) {
        Q[i] = Q[i - 1] + pref[i];
        for (int x = 0; x + v[i] - 1 <= MAX; x += v[i]) {
            Q[i] -= x * st1.query(x, x + v[i] - 1);
        }
        st1.upd(v[i], 1);
    }
    P[0] = 0;
    for (int i = 0; i < n; i++) {
        P[i] = P[max(i - 1, 0)] + v[i] * i;
        P[i] += st2.query(0, v[i]);
        for (int x = v[i]; x <= MAX; x += v[i]){
            st2.upd(x, st2.query(x, x) -v[i]);
        }
    }
    for (int i = 0; i < P.size(); i++) {
        cout << P[i] + Q[i] << " ";
    }
}
