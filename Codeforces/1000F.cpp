#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define pb push_back
#define mp make_pair

#define ll long long
using namespace std;
bool comp (pair<pair<int,int>,int> p, pair<pair<int,int>,int> q) {
    //sort by the right endpoint
    if (p.first.second == q.first.second) {
        return (p.first.second < q.first.second);
    }
    return (p.first.second < q.first.second);
}
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 1e9; T comb(T a, T b) { return min(a,b); }
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
int main() {
    int N;
    cin >> N;
    int a[N];
    Seg<int> st;
    st.init(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        st.upd(i, -1);
    }
    int Q;
    cin >> Q;
    vector<pair<pair<int,int>,int>> queries;
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries.push_back({{l, r}, i});
    }
    sort(queries.begin(), queries.end(), comp);
    int prev = -1;
    int lastOc[(int)5e5 + 1], prevOc[(int)5e5 + 1];
    for (int i: a) {
        lastOc[i] = prevOc[i] = -1;
    }
    vector<int> ans;
    ans.assign(Q, 0);
    for (auto& resp: queries) {
        int l = resp.first.first;
        int r = resp.first.second;
        int ind = resp.second;
        for (int i = prev + 1; i <= r; i++) {
            if (lastOc[a[i]] != -1) {
                st.upd(lastOc[a[i]], 1e9);
            }
            prevOc[a[i]] = lastOc[a[i]];
            lastOc[a[i]] = i;
            st.upd(i, prevOc[a[i]]);
        }
        prev = r;
        if (st.query(l, r) >= l) {
            continue;
        }
        int L = l;
        int R = r;
        while (L != R) {
            int M = (L + R)/2;
            if (st.query(l, M) < l) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        ans[ind] = a[L];
    }
    //return 0;
    for (int i: ans) {
        cout << i << '\n';
    }

}
