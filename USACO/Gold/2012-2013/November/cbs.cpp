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

using namespace std;
#define ll long long

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = (int)1e8; T comb(T a, T b) { return min(a,b); }
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
    Seg<int> st[K];
    vector<string> s(K);
    for (int i = 0; i < K; i++) {
        cin >> s[i];
        vector<int> depth = {0};
        st[i].init(s[i].length() + 2);
        st[i].upd(0, 0);
        for (int j = 0; j < s[i].length(); j++) {
            depth.push_back(depth.back() + conv(s[i][j]));
            st[i].upd(j + 1, depth.back());
        }
    }
    map<vector<int>, vector<int>> myMap;
    long long cntr = 0;
    for (int i = N - 1; i >= 0; i--) {
        vector<int> depths;
        for (int k = 0; k < K; k++) {
            depths.push_back(st[k].query(i + 1, i + 1));
        }
        vector<int> &vec = myMap[depths];
        if (vec.empty()) {
            myMap[depths].push_back(i);
            continue;
        }
        vector<int> v;
        for (int j = 0; j < K; j++) {
            v.push_back(st[j].query(i + 1, i + 1));
        }
        bool ok = true;
        for (int k = 0; k < K; k++) {
            if (st[k].query(i + 2, vec.back() + 1) < v[k]) {
                myMap[depths].push_back(i);
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        int l = 0;
        int r = (int)vec.size() - 1;
        while (l != r) {
            int m = (l + r) / 2;
            bool fine = true;
            for (int k = 0; k < K; k++) {
                if (st[k].query(i + 2, vec[m] + 1) < v[k]) {
                    fine = false;
                }
            }
            if (fine) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        cntr += vec.size() - l;
        myMap[depths].push_back(i);
    }
    cout << cntr << endl;
}
