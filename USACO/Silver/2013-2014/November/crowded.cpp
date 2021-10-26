#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll int
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return max(a,b);
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
    freopen("crowded.in", "r", stdin);
    freopen("crowded.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    int N, D;
    cin >> N >> D;
    st.resz(3 * N + 3);
    vector<pair<int,int>> vec(N);
    set<int> s;
    map<int,int> loc_to_height;
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
        s.insert(vec[i].first);
        loc_to_height[vec[i].first] = vec[i].second;
        s.insert(vec[i].first - D);
        s.insert(vec[i].first + D);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: s) {
        myMap[i] = cntr++;
    }
    for (int i = 0; i < vec.size(); i++) {
        st.update(myMap[vec[i].first], vec[i].second);
    }
    cntr = 0;
    for (int i = 0; i < vec.size(); i++) {
        int x = myMap[vec[i].first];
        if (st.query(myMap[vec[i].first - D], x) >= 2 * vec[i].second) {
            if (st.query(x, myMap[vec[i].first + D]) >= 2 * vec[i].second) {
                cntr++;
            }
        }
    }
    cout << cntr << endl;
}
