#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <random>
#include <array>
#include <chrono>

using namespace std;

typedef int64_t ll;
struct Node {
    int x;
    Node *l = 0;
    Node *r = 0;
    Node *p = 0;
    bool rev = false;

    Node() = default;

    Node(int v) {
        x = v;
    }

    void push() {
        if(rev) {
            rev = false;
            swap(l, r);
            if(l) l->rev ^= true;
            if(r) r->rev ^= true;
        }
    }

    bool is_root() {
        return p == 0 || (p->l != this && this != p->r);
    }
};

struct LCT {
    vector<Node> a;

    LCT(int n) {
        a.resize(n+1);
        for(int i = 1; i <= n; ++i)
            a[i].x = i;
    }

    void rot(Node* c) {
        auto p = c->p;
        auto g = p->p;

        if(!p->is_root())
            (g->r == p ? g->r : g->l) = c;

        p->push();
        c->push();

        if(p->l == c) { // rtr
            p->l = c->r;
            c->r = p;
            if(p->l) p->l->p = p;
        } else { // rtl
            p->r = c->l;
            c->l = p;
            if(p->r) p->r->p = p;
        }

        p->p = c;
        c->p = g;
    }

    void splay(Node* c) {
        while(!c->is_root()) {
            auto p = c->p;
            auto g = p->p;
            if(!p->is_root())
                rot((g->r == p) == (p->r == c) ? p : c);
            rot(c);
        }
        c->push();
    }

    Node* access(int v) {
        Node* last = 0;
        Node* c = &a[v];
        for(Node* p = c; p; p = p->p) {
            splay(p);
            p->r = last;
            last = p;
        }
        splay(c);
        return last;
    }

    void make_root(int v) {
        access(v);
        auto* c = &a[v];
        if(c->l)
            c->l->rev ^= true, c->l = 0;
    }

    void link(int u, int v) {
        make_root(v);
        Node* c = &a[v];
        c->p = &a[u];
    }

    void cut(int u, int v) {
        make_root(u);
        access(v);
        if(a[v].l) {
            a[v].l->p = 0;
            a[v].l = 0;
        }
    }

    bool connected(int u, int v) {
        access(u);
        access(v);
        return a[u].p;
    }
};

int firstOc (vector<ll>& v, int x) {
    int l = 0;
    int r = v.size();
    while (l != r) {
        int mid = (l + r)/2;
        if (v[mid] >= x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, M;
    cin >> N >> M;
    LCT lct(N);
    vector<vector<ll>> adj(N);
    for (ll i = 0; i < M; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    ll l = 0;
    ll r = 0;
    vector<ll> arr(N);
    for (ll i = 0; i < N; i++) {
        arr[i] = -1;
    }
    while (l != N - 1) {
        arr[l] = r;
        bool okay = true;
        vector<pair<ll, ll>> added;
        if (r != N - 1) {
            for (ll i: adj[r + 1]) {
                if (i < l || i > r) continue;
                assert(i >= l && i <= r);
                if (lct.connected(i, r + 1)) {
                    okay = false;
                    break;
                }
                added.emplace_back(i, r + 1);
                lct.link(added.back().first, added.back().second);
            }
        } else {
            okay = false;
        }
        if (okay) {
            r++;
            continue;
        }
        for (auto& p: added) {
            lct.cut(p.first, p.second);
        }
        for (ll i: adj[l]) {
            if (i < l || i > r) continue;
            assert(i >= l && i <= r);
            lct.cut(i, l);
        }
        l++;
    }
    for (ll i = 0; i < N; i++) {
        if (arr[i] == -1) {
            arr[i] = N - 1;
        }
    }
    ll pref[N + 1];
    pref[0] = 0;
    for (ll i = 1; i <= N; i++) {
        pref[i] = pref[i - 1] + arr[i - 1];
    }
    ll Q;
    cin >> Q;
    while (Q--) {
        ll left, right;
        cin >> left >> right;
        left--, right--;
        ll ans = -(right + left) * (right - left + 1)/2 + right - left + 1;
        ll x = firstOc(arr, right);
        if (x < left) x = left;
        ans += pref[x] - pref[left];
        ans += (right - x + 1) * right;
        cout << ans << '\n';
    }
}
