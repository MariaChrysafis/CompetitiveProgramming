#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;
const ll MOD = 1e9 + 7;
void solve() {
    int N, G;
    cin >> N >> G;
    vector<vector<int>> v(G);
    vector<int> cnt;
    cnt.assign(G, false);
    map<int,vector<int>> oc;
    for (int i = 0; i < G; i++) {
        int n;
        cin >> n;
        set<int> s;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            s.insert(x);
        }
        for (int j: s) {
            v[i].push_back(j);
        }
        for (int j = 0; j < v[i].size(); j++) {
            oc[v[i][j]].push_back(i);
        }
    }
    set<int> hv;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        //cout << cur << '\n';
        q.pop();
        if (hv.count(cur)) {
            continue;
        }
        hv.insert(cur);
        for (int j: oc[cur]) {
            cnt[j]++;
            if (cnt[j] == v[j].size() - 1) {
                for (int x: v[j]) {
                    if (!hv.count(x)) {
                        q.push(x);
                    }
                }
            }
        }
    }
    int cntr = 0;
    for (auto& p: hv) {
        cntr++;
    }
    cout << cntr << '\n';
}
int main() {
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);
    solve();
}
