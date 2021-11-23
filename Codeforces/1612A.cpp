#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll __int128
using namespace std;
void solve() {
    int x, y;
    cin >> x >> y;
    if ((abs(x) + abs(y)) % 2 == 1) {
        cout << "-1 -1\n";
        return;
    }
    for (int i = 0; i <= 100; i++) {
        int j = (abs(x) + abs(y))/2 - i;
        if (abs(i - x) + abs(j - y) == ((abs(x)) + abs(y))/2) {
            cout << i << " " << j << '\n';
            return;
        }
    }
    cout << "-1 -1\n";
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
