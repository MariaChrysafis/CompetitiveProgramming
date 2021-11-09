#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

using namespace std;
#define ll long long

struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = (int) 1e8;

    ll op(ll a, ll b) {
        return min(a, b);
    }

    ll query(int dum, int tl, int tr, int &l, int &r) {
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
        return query(1, 0, (int) v.size() - 1, l, r);
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
            if (cur % 2 == 0) {
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

int conv(char c) {
    if (c == '(') return 1;
    else return -1;
}

int main() {
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int K, N;
    cin >> K >> N;
    segmentTree st[K];
    vector<string> s(K);
    for (int i = 0; i < K; i++) {
        cin >> s[i];
        vector<int> depth = {0};
        st[i].resz(s[i].length() + 1);
        st[i].update(0, 0);
        for (int j = 0; j < s[i].length(); j++) {
            depth.push_back(depth.back() + conv(s[i][j]));
            st[i].update(j + 1, depth.back());
        }
    }
    map<vector<int>, vector<int>> myMap;
    long long cntr = 0;
    for (int i = N - 1; i >= 0; i--) {
        vector<int> depths;
        for (int k = 0; k < K; k++) {
            depths.push_back(st[k].query(i + 1, i + 1));
        }
        if (myMap[depths].empty()) {
            myMap[depths].push_back(i);
            continue;
        }
        bool ok = true;
        for (int k = 0; k < K; k++) {
            if (st[k].query(i + 2, myMap[depths].back() + 1) < st[k].query(i + 1, i + 1)) {
                myMap[depths].push_back(i);
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        int l = 0;
        int r = (int)myMap[depths].size() - 1;
        while (l != r) {
            int m = (l + r) / 2;
            bool fine = true;
            for (int k = 0; k < K; k++) {
                if (st[k].query(i + 2, myMap[depths][m] + 1) < st[k].query(i + 1, i + 1)) {
                    fine = false;
                }
            }
            if (fine) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        assert(l == r);
        cntr += myMap[depths].size() - l;
        myMap[depths].push_back(i);
    }
    cout << cntr << endl;
}
