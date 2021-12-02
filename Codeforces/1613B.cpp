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
#include <algorithm>
#pragma GCC optimize("Ofast")

#define ll int
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }
    sort(a.begin(), a.end());
    vector<pair<int,int>> vec;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!s.count(a[j] % a[i])) {
                vec.push_back({a[j], a[i]});
                if (vec.size() == n/2) {
                    break;
                }
            }
        }
        if (vec.size() == n/2) {
            break;
        }
    }
    for (auto& p: vec) {
        cout << p.first << " " << p.second << '\n';
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
