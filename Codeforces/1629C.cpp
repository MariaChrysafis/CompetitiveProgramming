#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

vector<int> cur;
vector<int> v;
vector<int> suf;

void get_best (int l, int r) {
    if (l > r) {
        return;
    }
    int mx = suf[l];
    cur.push_back(mx);
    bool cnt[mx];
    for (int i = 0; i < mx; i++) {
        cnt[i] = false;
    }
    int cntr = 0;
    for (int i = l; i <= r; i++) {
        if (v[i] < mx && cnt[v[i]] == false) {
            cnt[v[i]] = true;
            cntr++;
        }
        if (cntr == mx) {
            get_best(i + 1, r);
            break;
        }
    }
}

void solve () {
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    suf.resize(v.size() + 1);
    suf[v.size()] = 0;
    vector<bool> oc(v.size() + 2);
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        oc[v[i]] = true;
        suf[i] = suf[i + 1];
        while (oc[suf[i]]) {
            suf[i]++;
        }
    }
    get_best(0, n - 1);
    cout << cur.size() << '\n';
    for (int i: cur) {
        cout << i << ' ';
    }
    cout << '\n';
    cur.clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
