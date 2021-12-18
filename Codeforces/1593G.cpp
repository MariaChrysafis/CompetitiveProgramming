#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;
void solve() {
    string s;
    cin >> s;
    int Q;
    cin >> Q;
    int pref[(int)s.length() + 1][2];
    pref[0][0] = pref[0][1] = 0;
    for (int i = 0; i < s.length(); i++) {
        pref[i + 1][0] = pref[i][0];
        pref[i + 1][1] = pref[i][1];
        pref[i + 1][i % 2] += (s[i] == ']' || s[i] == '[');
    }
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int odd = pref[r + 1][0] - pref[l][0];
        int even = pref[r + 1][1] - pref[l][1];
        cout << abs(even - odd) << '\n';
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
