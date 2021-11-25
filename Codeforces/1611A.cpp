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
#define ll long long
using namespace std;
void solve () {
    string s;
    cin >> s;
    if ((s.back() - '0') % 2 == 0) {
        cout << 0 << '\n';
        return;
    }
    if ((s[0] - '0') % 2 == 0) {
        cout << 1 << '\n';
        return;
    }
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] - '0') % 2 == 0) {
            cnt++;
        }
    }
    if (cnt) {
        cout << 2 << '\n';
        return;
    }
    cout << "-1\n";
    return;
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
