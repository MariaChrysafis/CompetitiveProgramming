#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;


struct segmentTreePoint {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int> p(N), ind(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        ind[p[i]] = i;
    }
    vector<vector<int>> adj(N);
    for (int i = 1; i <= N; i++) {
        for (int j = 2 * i; j <= N; j += i) {
            adj[ind[j]].push_back(ind[i]); //represents our set of edges
            adj[ind[i]].push_back(ind[j]); //represents our set of edges
            //cout << ind[i] << " " << ind[j] << '\n';
        }
    }
    vector<pair<pair<int,int>,int>> vec[N];
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        vec[l].push_back({{l, r}, i});
    }
    segmentTreePoint st;
    st.resz(N);
    int ans[Q];
    for (int i = N - 1; i >= 0; i--) {
        for (int j: adj[i]) {
            if (j < i) continue;
            st.upd(j, N - 1, 1);
        }
        for (auto& p: vec[i]) {
            ans[p.second] = st.get(p.first.second) + abs(p.first.first - p.first.second) + 1;
        }
    }
    for (int i: ans) {
        cout << i << '\n';
    }
    cout << '\n';
}
