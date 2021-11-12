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

struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return min(a,b);
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
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
    vector<int> gain(N); //how much will we gain by skipping this interval (maximal lost cost)
    for (int i = 0; i < N; i++) {
        cin >> vec[i].x >> vec[i].y;
        gain[i] = 0;
    }
    segmentTreePoint st;
    st.resz(N + 3);
    vector<int> dist(N + 1); //distance if we use the first X courses
    dist[0] = dist[1] = 0;
    for (int i = 2; i <= N; i++) {
        dist[i] = dist[i - 1] + (vec[i - 1].dist(vec[i - 2]));
        st.upd(i, i, dist[i - 1] + (vec[i - 1].dist(vec[i - 2])));
    }
    segmentTree st1;
    st1.resz(N + 1);
    for (int i = 1; i < N; i++) {
        gain[i] = vec[i - 1].dist(vec[i + 1]) - vec[i - 1].dist(vec[i]) - vec[i].dist(vec[i + 1]);
        st1.update(i, gain[i]);
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
                    st1.update(i, vec[i - 1].dist(vec[i + 1]) - vec[i].dist(vec[i - 1]) - vec[i].dist(vec[i + 1]));
                }
            }
        }
    }
}
