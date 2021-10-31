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
    int cntr = 0;
    int div2 = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int prev = 0;
    for (int i = 0; i < n; i++) {
        bool fine = false;
        for (int j = 0; j <= min(i, 100); j++) {
            if (v[i] % (j + 2) != 0) {
                fine = true;
                prev = j;
                break;
            }
        }
        if (!fine) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
