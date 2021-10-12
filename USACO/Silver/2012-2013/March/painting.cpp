#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;
struct Point {
    int x, y;
};
struct Rectangle {
    Point p1, p2;
};
Point read() {
    Point p;
    cin >> p.x >> p.y;
    return p;
}

struct segmentTree {
    vector<int> v;
    vector<int> val;

    int ID = 0;

    int query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        return query(dum, tl, mid, l, r) + query(dum + 1, mid + 1, tr, l, r);
    }

    int query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, int y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = query(curX, x - 1) + query(x + 1, curY) + y;
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
vector<Rectangle> compressed (vector<Rectangle> inp) {
    vector<pair<pair<int,int>, bool>> vec;
    for (int i = 0; i < inp.size(); i++) {
        vec.push_back({{inp[i].p1.y, i}, true});
        vec.push_back({{inp[i].p2.y, i}, false});
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        auto p = vec[i];
        int ind = p.first.second;
        if(p.second) inp[ind].p1.y = i;
        else inp[ind].p2.y = i;
    }
    return inp;
}
int main() {
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector <Rectangle> v;
    segmentTree st;
    st.resz(2 * n + 2);
    for (int i = 0; i < n; i++) {
        Rectangle r;
        r.p1 = read(), r.p2 = read();
        v.push_back(r);
    }
    v = compressed(v);
    vector <pair<pair<int,char>, int>> vec;
    for (int i = 0; i < n; i++) {
        vec.emplace_back(make_pair(make_pair(v[i].p1.x, 'S'), i));
        vec.emplace_back(make_pair(make_pair(v[i].p2.x, 'E'), i));
    }
    sort (vec.begin(), vec.end());
    int cntr = 0;
    for (int i = 0; i < vec.size(); i++) {
        int ind = vec[i].second;
        if (vec[i].first.second == 'S') {
            if (st.query(v[ind].p1.y, 2 * n + 1) == 0) {
                cntr++;
            }
            st.update(v[ind].p1.y, 1);
            st.update(v[ind].p2.y, -1);
        } else {
            st.update(v[ind].p1.y, 0);
            st.update(v[ind].p2.y, 0);
        }
    }
    cout << cntr << endl;
}
