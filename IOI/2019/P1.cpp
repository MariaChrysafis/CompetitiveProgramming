#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
//#include "shoes.h"

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
using namespace std;
struct segmentTree {
    vector<int64_t> v;
    vector<int64_t> val;

    int64_t ID = 0;

    int64_t op(int64_t a, int64_t b) {
        return a + b;
    }

    int64_t query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        int64_t mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    int64_t query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, int64_t y) {
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

int64_t get_inversions (vector<int> v) {
    segmentTree st;
    st.resz(v.size() + 3);
    int64_t ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ans += st.query(v[i] + 1, v.size() + 2);
        st.update(v[i], st.query(v[i], v[i]) + 1);
    }
    return ans;
}

long long count_swaps (vector<int> v) {
    map<int,set<int>> myMap;
    for (int i = 0; i < v.size(); i++) {
        myMap[v[i]].insert(i);
    }
    vector<int> vec(v.size());
    int cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < 0) {
            int x = *myMap[-v[i]].begin();
            myMap[-v[i]].erase(x);
            vec[i] = cntr++;
            vec[x] = cntr++;
        }
    }
    return get_inversions(vec);
}


int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << count_swaps({-1, 1, -1, -1, 1, 1});
}
