#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
struct Node {
    int a, b, c, ab, bc, abc;
    bool operator== (Node& x) const {
        return (x.a == a && x.b == b && x.c == c && x.ab == ab && x.bc == bc && x.abc == abc);
    }
    Node () {
        a = b = c = ab = bc = abc = 0;
    }
};
Node dummy;
Node construct (char c) {
    Node ans;
    ans.a = (c == 'a');
    ans.b = (c == 'b');
    ans.c = (c == 'c');
    assert(ans.a + ans.b + ans.c == 1);
    return ans;
}
Node merge (Node x1, Node x2) {
    Node ans;
    ans.a = x1.a + x2.a, ans.b = x1.b + x2.b, ans.c = x1.c + x2.c;
    ans.ab = min(x1.ab + x2.b, x1.a + x2.ab);
    ans.bc = min(x1.bc + x2.c, x1.b + x2.bc);
    ans.abc = min({x1.abc + x2.c, x1.a + x2.abc, x1.ab + x2.bc});
    return ans;
}
struct segmentTree {
    vector<Node> v;
    vector<Node> val;
    Node query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return dummy;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        return merge(query(2 * dum, tl, mid, l, r), query(2 * dum + 1, mid + 1, tr, l, r));
    }

    Node query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, char y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = merge(merge(query(curX, x - 1), construct(y)), query(x + 1, curY));
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    segmentTree st;
    st.resz(n);
    for (int i = 0; i < n; i++) {
        st.update(i, s[i]);
    }
    while (m--) {
        int ind; char c;
        cin >> ind >> c;
        ind--;
        st.update(ind, c);
        cout << st.query(0, n - 1).abc << '\n';
    }
}
