#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
set<int> s;
struct Node {
    map<int,int> dp;
    map<int,int> oc;
    int sum3;
};
//set<int> s;
Node merge(Node a, Node b) {
    Node ans;
    ans.sum3 = 0;
    for (auto p: a.oc) {
        ans.oc[p.first] = p.second;
    }
    for (auto p: b.oc) {
        ans.oc[p.first] += p.second;
    }
    for (auto p: a.dp) {
        ans.dp[p.first] += p.second;
    }
    for (auto p: b.dp) {
        ans.dp[p.first] += p.second;
    }
    for (auto p1: a.oc) {
        for (int i: s) {
            ans.dp[i] += a.oc[p1.first] * b.oc[i - p1.first];
        }
    }
    ans.sum3 = a.sum3 + b.sum3;
    for (auto p1: a.dp) {
        ans.sum3 += p1.second * b.oc[-p1.first];
    }
    for (auto p1: b.dp) {
        ans.sum3 += p1.second * a.oc[-p1.first];
    }
    return ans;
}
Node construct(int x) {
    Node ans;
    ans.oc[x] = 1;
    ans.sum3 = 0;
    return ans;
}
map<int,int> empty_map;
struct segmentTree {
    vector<Node> v;
    vector<Node> val;

    Node ID = {empty_map, empty_map};

    Node query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        return merge(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    Node query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, int y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = merge(merge(query(curX, x - 1), query(x + 1, curY)), construct(y));
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
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    segmentTree st;
    st.resz(n + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.update(i, x);
        s.insert(x), s.insert(-x);
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << st.query(a, b).sum3 << endl;
    }
    //cout << sum3(construct(3)) << endl;
    return 0;
}


