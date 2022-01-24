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

using namespace std;
typedef long long ll;
vector<map<int,int>> indices;
void chmax (int&x , int y) {
    x = max(x, y);
}
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return max(a,b);
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
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
        return query(1, 0, (int)v.size() - 1, l, r);
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
vector<set<int>> s;
class Graph {
public:
    vector<segmentTree> dp;
    int myMax = 0;
    Graph (int n) {
        dp.resize(n);
    }
    void add_edge (int u, int v, int w) {
        //cout << *s[u].lower_bound(w) << '\n';
        int ans = dp[u].query(0, indices[u][w] - 1);
        if (ans + 1 > dp[v].query(indices[v][w], indices[v][w])) {
            dp[v].update(indices[v][w], ans + 1);
        }
        myMax = max(myMax, ans + 1);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    Graph g(N);
    s.resize(N);
    vector<pair<pair<int,int>,int>> vec;
    for (int i = 0; i < M; i++) {
       int u, v, w;
       cin >> u >> v >> w;
       vec.push_back({{u - 1, v- 1}, w});
       s[u - 1].insert(w);
       s[v - 1].insert(w);
    }
    indices.resize(N);
    for (int i = 0; i < s.size(); i++) {
        int cntr = 1;
        for (int j: s[i]) {
            indices[i][j] = cntr++;
        }
        g.dp[i].resz(cntr);
    }
    for (auto& p: vec) {
        g.add_edge(p.first.first, p.first.second, p.second);
    }
    cout << g.myMax;
}
