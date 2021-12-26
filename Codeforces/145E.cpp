#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef int ll;
using namespace std;

struct Node {
    int n4;
    int n7;
    int n47;
    int n74;
};

struct segmentTree {
    vector<Node> vec;
    vector<ll> addLater;

    Node op(Node a, Node b) {
        return {a.n4 + b.n4, a.n7 + b.n7, max(a.n47 + b.n7, a.n4 + b.n47), max(a.n74 + b.n4, a.n7 + b.n74)};
    }

    Node &rev(Node &a) {
        swap(a.n4, a.n7);
        swap(a.n47, a.n74);
        return a;
    }

    void push(int v) {
        if (!addLater[v]) {
            return;
        }
        addLater[2 * v + 1] = !addLater[2 * v + 1];
        swap(vec[2 * v + 1].n4, vec[2 * v + 1].n7);
        swap(vec[2 * v + 1].n47, vec[2 * v + 1].n74);
        addLater[2 * v] = !addLater[2 * v];
        swap(vec[2 * v].n4, vec[2 * v].n7);
        swap(vec[2 * v].n47, vec[2 * v].n74);
        addLater[v] = false;
    }

    void upd(int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] = !addLater[dum];
            vec[dum] = rev(vec[dum]);
            return;
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r);
        upd(2 * dum + 1, mid + 1, tr, l, r);
        vec[dum] = op(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void pull(int p) {
        vec[p] = op(vec[2 * p], vec[2 * p + 1]);
    }

    void upd(int p, Node val) {
        vec[p += vec.size() / 2] = val;
        for (p /= 2; p; p /= 2){
            pull(p);
            push(p);
        }
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.assign(sz * 2, false);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    segmentTree st;
    st.resz(n + 1);
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '4') {
            st.upd(i, {1, 0, 1, 1});
        } else {
            st.upd(i, {0, 1, 1, 1});
        }
    }
    while (q--) {
        string str;
        cin >> str;
        if (str == "count") {
            st.push(1);
            cout << st.vec[1].n47 << '\n';
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            st.upd(l, r);
        }
    }

}
