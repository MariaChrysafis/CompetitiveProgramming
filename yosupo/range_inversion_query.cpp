#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a+b; }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] += val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};

int64_t ans = 0;
Seg<int64_t> st;
int N;

void add_right (int x) {
    ans += st.query(x + 1, N);
    st.upd(x, 1);
}

void add_left (int x) {
    ans += st.query(0, x - 1);
    st.upd(x, 1);
}

void remove_right (int x) {
    ans -= st.query(x + 1, N);
    st.upd(x, -1);
}

void remove_left (int x) {
    ans -= st.query(0, x - 1);
    st.upd(x, -1);
}

bool comp (pair<pair<int,int>,int> p3, pair<pair<int,int>,int> p4) {
    auto p1 = p3.first;
    auto p2 = p4.first;
    return (pair<int,int>){p1.first/400, p1.second} < (pair<int,int>){p2.first/400, p2.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> N >> Q;
    st.init(N + 1);
    int arr[N];
    set<int> s;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: s) {
        myMap[i] = cntr++;
    }
    for (int i = 0; i < N; i++) {
        arr[i] = myMap[arr[i]];
    }
    vector<pair<pair<int,int>,int>> vec(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        r--;
        vec[i] = {{l, r}, i};
    }
    sort(vec.begin(), vec.end(), comp);
    int tl = 0;
    int tr = -1;
    int64_t q[Q];
    for (auto& p: vec) {
        while (tl > p.first.first) {
            add_left(arr[--tl]);
        }
        while (tl < p.first.first) {
            remove_left(arr[tl++]);
        }
        while (tr > p.first.second) {
            remove_right(arr[tr--]);
        }
        while (tr < p.first.second) {
            add_right(arr[++tr]);
        }
        q[p.second] = ans;
    }
    for (int64_t i: q) {
        cout << i << '\n';
    }
}
