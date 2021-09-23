#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

vector<int> lazy;
vector<int> t;
const int INF = 1e9;

void push(int v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

void update(int l, int r, int addend) {
    update(1, 0, 32767, l, r, addend);
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INF;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)),
               query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

int query(int l, int r) {
    return query(1, 0, 32767, l, r);
}

void solve() {
    t.resize(65534), lazy.resize(65534);
    int n, m;
    cin >> n >> m;
    vector<int> v(n * m + 1);
    for(int i = 1; i <= n * m; i++) {
        cin >> v[i];
    }
    map<int,int> lastOc;
    map<int,bool> done;
    vector<pair<int,int>> ans(n);
    for(int i = 1; i <= n * m; i++) {
        if (done[v[i]]) {
            continue;
        }
        if(lastOc[v[i]] != 0) {
            update(lastOc[v[i]], i, 1);
            if(query(lastOc[v[i]], i) > (n + m - 2)/(m - 1)) {
                update(lastOc[v[i]], i, -1);
            } else {
                done[v[i]] = true;
                ans[v[i] - 1] = {lastOc[v[i]], i};
            }
        }
        lastOc[v[i]] = i;
    }
    for(pair<int,int> p: ans) {
        cout << p.first << " " << p.second << endl;
    }
}

int main() {
    solve();
}
 
