#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>

#define ll long long

#include <map>

using namespace std;

struct Coord {
    int x, y;

    int dist(Coord c) {
        return abs(c.x - x) + abs(c.y - y);
    }
};


struct segmentTreePoint {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }

};

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return min(a,b); }
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
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<Coord> vec(N);
    vector<int> gain(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i].x >> vec[i].y;
        gain[i] = 0;
    }
    segmentTreePoint st;
    st.resz(N + 3);
    vector<int> dist(N + 1);
    dist[0] = dist[1] = 0;
    for (int i = 2; i <= N; i++) {
        dist[i] = dist[i - 1] + (vec[i - 1].dist(vec[i - 2]));
        st.upd(i, i, dist[i - 1] + (vec[i - 1].dist(vec[i - 2])));
    }
    Seg<int> st1;
    st1.init(N + 1);
    for (int i = 1; i < N; i++) {
        gain[i] = vec[i - 1].dist(vec[i + 1]) - vec[i - 1].dist(vec[i]) - vec[i].dist(vec[i + 1]);
        st1.upd(i, gain[i]);
    }
    while (Q--) {
        char c;
        cin >> c;
        if (c == 'Q') {
            int i, j;
            cin >> i >> j;
            int base = st.get(j) - st.get(i);
            i--, j--;
            int myMin = st1.query(i + 1, j - 1);
            cout << base + myMin << '\n';
        } else {
            int ind, x, y;
            cin >> ind >> x >> y;
            ind--;
            if (ind >= 0) {
                st.upd(ind + 1, N, vec[ind - 1].dist({x, y}) - vec[ind - 1].dist(vec[ind]));
            }
            st.upd(ind + 2, N, vec[ind + 1].dist({x, y}) - vec[ind + 1].dist(vec[ind]));
            vec[ind] = {x, y};
            for (int i = ind - 1; i <= ind + 1; i++) {
                if (i - 1 >= 0 && i + 1 < gain.size()) {
                    gain[i] = vec[i - 1].dist(vec[i + 1]) - vec[i].dist(vec[i - 1]) - vec[i].dist(vec[i + 1]);
                    st1.upd(i, vec[i - 1].dist(vec[i + 1]) - vec[i].dist(vec[i - 1]) - vec[i].dist(vec[i + 1]));
                }
            }
        }
    }
}
