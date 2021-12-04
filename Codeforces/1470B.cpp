#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

string s;

bool good (string ans, int n, int k) {
    if (ans.size() != n) return false;
    map<char,int> oc;
    for (char c: ans) oc[c]++;
    for (auto& p: oc) {
        if (p.second % k != 0) {
            return false;
        }
    }
    return true;
}

void solve () {
    int n; cin >> n;
    vector<int> v(n);
    map<int,int> oc;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        for (int j = 2; j <= 1000; j++) {
            while (v[i] % (j * j) == 0) {
                v[i] /= j * j;
            }
        }
        if (floor(sqrt(v[i])) * floor(sqrt(v[i])) == v[i]) {
            v[i] = 1;
        }
        //cout << v[i] << ' ';
        oc[v[i]]++;
    }
    int myMax = 0;
    for (auto& p: oc) {
        myMax = max(myMax, p.second);
    }
    for (auto& p: oc) {
        if (p.first == 1) continue;
        if (p.second % 2 == 0) oc[1] += p.second, p.second = 0;
    }
    int q; cin >> q;
    while (q--) {
        ll x; cin >> x;
        if (x == 0) {
            cout << myMax << '\n';
        } else {
            cout << max(myMax, oc[1]) << '\n';
        }
    }
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
