#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

struct Tree {
    vector<ll> parent;
    vector<vector<ll>> binJump;
    vector<pair<ll, ll>> vec;

    ll access(ll cur, ll a) {
        if (cur == -1) {
            return -1;
        }
        if (a == 0) {
            return cur;
        }
        ll mostSignificantBit = floor(log2(a));
        cur = binJump[cur][mostSignificantBit];
        return access(cur, a - (1 << mostSignificantBit));
    }

    ll binSearch(ll curNode, ll l, ll r) {
        //find the next best node which is not already marked
        if (curNode == 0) {
            return curNode;
        }
        if (l == r) {
            return access(curNode, l);
        }
        ll m = (l + r + 1) >> 1;
        ll node = access(curNode, m);
        if (node == -1 || vec[node].first == 0) {
            return binSearch(curNode, l, m - 1);
        } else {
            return binSearch(curNode, m, r);
        }
    }

    void add_edge(ll cur, ll par, ll a, ll c) {
        while (binJump.size() <= cur) {
            binJump.emplace_back();
            binJump.back().resize(20);
            parent.emplace_back();
            vec.emplace_back();
        }
        parent[cur] = par;
        vec[vec.size() - 1] = make_pair(a, c);
        binJump[cur][0] = par;
        for (int i = 1; i < binJump[0].size(); i++) {
            if (binJump[cur][i - 1] == -1) {
                binJump[cur][i] = -1;
                continue;
            }
            binJump[cur][i] = binJump[binJump[cur][i - 1]][i - 1];
        }
    }

    pair<ll, ll> take(ll cur, ll gold) {
        ll ans2 = 0;
        ll ans1 = 0;
        if(vec[cur].first == 0) {
            //cout << "YES\n";
            return make_pair(0, 0);
        }
        while (true) {
            ll nextNode = binSearch(cur, 0, vec.size());
            //cout << nextNode << endl;
            if (vec[nextNode].first == 0) {
                break;
            }
            ll take = min(vec[nextNode].first, gold);
            ans2 += take * vec[nextNode].second;
            ans1 += take;
            vec[nextNode].first -= take;
            gold -= take;
            if (vec[nextNode].first != 0) {
                break;
            }
        }
        return make_pair(ans1, ans2);
    }
};

int main() {
    Tree tree;
    ll q, a0, c0;
    cin >> q >> a0 >> c0;
    tree.add_edge(0, -1, a0, c0);
    for (int tc = 1; tc <= q; tc++) {
        ll t;
        cin >> t;
        if (t == 2) {
            long long vi, wi;
            cin >> vi >> wi;
            pair<ll, ll> p = tree.take(vi, wi);
            cout << p.first << " " << p.second << endl;
        } else {
            long long pi, ai, ci;
            cin >> pi >> ai >> ci;
            tree.add_edge(tc, pi, ai, ci);
        }
    }
}
