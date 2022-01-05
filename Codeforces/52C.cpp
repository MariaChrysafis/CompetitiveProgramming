#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;

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

    const ll INF = 1e18;

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
        return (vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int val) {
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
        return min(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    int N;
    cin >> N;
    st.resz(N);
    int a[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        st.upd(i, i, a[i]);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        if (cin.get() == '\n') {
            if (l <= r) {
                cout << st.get(l, r) << '\n';
            } else {
                cout << min(st.get(0, r), st.get(l, N - 1)) << '\n';
            }
        } else {
            int k;
            cin >> k;
            if (l <= r) {
                st.upd(l, r, k);
            } else {
                st.upd(0, r, k);
                st.upd(l, N - 1, k);
            }
        }
    }

}
