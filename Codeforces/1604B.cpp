#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long

void solve() {
    int n;
    cin >> n;
    vector<ll> v(n);
    ll XOR = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        XOR ^= v[i];
    }
    if (n % 2 == 0) {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        if (v[i] >= v[i + 1]) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
