#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
struct Node {
    int oc[26];
};
Node em;
struct SegmentTree {
    vector<Node> vec;
    vector<char> setLater;

    Node op(Node a, Node b) {
        Node ans;
        for (int i = 0; i < 26; i++) {
            ans.oc[i] = a.oc[i] + b.oc[i];
        }
        return ans;
    }

    void clear (int ind) {
        for (int i = 0; i < 26; i++) {
            vec[ind].oc[i] = 0;
        }
    }

    void push(int v, int tl, int tr) {
        if (setLater[v] == '?') {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        setLater[2 * v] = setLater[v];
        clear(2 * v);
        clear(2 * v + 1);
        vec[2 * v + 1].oc[setLater[v] - 'a'] = tr - tm;
        vec[2 * v].oc[setLater[v] - 'a'] = tm - tl + 1;
        setLater[v] = '?';
    }

    void upd(int dum, int tl, int tr, int l, int r, char val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            clear(dum);
            vec[dum].oc[val - 'a'] = tr - tl + 1;
            return;
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        vec[dum] = op(vec[2 * dum], vec[2 * dum + 1]);
    }

    void upd(int l, int r, char val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    Node get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return em;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return op(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    Node get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, em);
        setLater.assign(sz * 2, '?');
    }

};
int N;
SegmentTree st;
void print () {
    for (int i = 0; i < N; i++) {
        Node a = st.get(i, i);
        for (int j = 0; j < 26; j++) {
            if (a.oc[j] == 1) {
                cout << (char)('a' + j);
            }
        }
    }
}
void print (Node a) {
    for (int i = 0; i < 26; i++) {
        cout << (char) ('a' + i) << a.oc[i] << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> N >> Q;
    st.resz(N);
    string s;
    cin >> s;
    for (int i = 0; i < N; i++) {
        st.upd(i, i, s[i]);
    }
    while (Q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        Node myNode = st.get(l, r);
        vector<char> order;
        for (char c = 'a'; c <= 'z'; c++) {
            order.push_back(c);
        }
        if (k == 0) {
            reverse(order.begin(), order.end());
        }
        vector<pair<pair<int,int>,char>> vec;
        for (char c: order) {
            if (myNode.oc[c - 'a'] == 0) {
                continue;
            }
            if (vec.empty()) {
                vec.push_back({{l, l + myNode.oc[c - 'a'] - 1}, c});
            } else {
                vec.push_back({{vec.back().first.second + 1, vec.back().first.second + myNode.oc[c - 'a']}, c});
            }
        }
        for (auto& p: vec) {
            st.upd(p.first.first, p.first.second, p.second);
        }
    }
    print();
}
