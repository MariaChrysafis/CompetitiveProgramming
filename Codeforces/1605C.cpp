#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int len = 2; len <= min((int)s.length(), 10); len++) {
        for (int i = 0; i <= s.length() - len; i++) {
            int oc[3];
            oc[0] = oc[1] = oc[2] = 0;
            for (int j = 0; j <= len - 1; j++) {
                oc[s[i + j] - 'a']++;
            }
            if (oc[0] > oc[1] && oc[0] > oc[2]) {
                cout << len << '\n';
                return;
            }
        }
    }
    cout << -1 << '\n';
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
