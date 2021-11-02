#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
 
#define ll long long
using namespace std;
 
struct segmentTree {
    vector<ll> vec;
    vector<ll> addLater;
 
    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }
 
    const ll INF = -(ll)1e17;
 
    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        ll left = upd(2 * dum, tl, mid, l, r, val);
        ll right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = max(vec[2 * dum], vec[2 * dum + 1]));
    }
 
    void upd(int l, int r, ll val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }
 
    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return max(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }
 
    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }
 
    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 4);
        addLater.resize(sz * 4);
    }
 
};
segmentTree st;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    st.resz(n + 2);
    ll pref = 0;
    ll myMax = -(ll)1e17;
    for (int i = 0; i < n; i++) {
        pref += arr[i];
        if (i + 1 >= a && i + 1 <= b) {
            myMax = max(myMax, pref);
        }
        st.upd(i + 1, i + 1, pref); //lenght
    }
    for (int i = 0; i < n; i++) {
        myMax = max(myMax, st.get(a + i, min(b + i, n -1)));
        st.upd(i + 1, n, -arr[i]);
    }
    vector<ll> suf = {0};
    for (int i = n - 1; i >= 0; i--) {
        suf.push_back(suf.back() + arr[i]);
    }
    for (int i = 0; i < suf.size(); i++) {
        if (i >= a && i <= b) {
            myMax = max(myMax, suf[i]);
        }
    }
    cout << myMax;
}
