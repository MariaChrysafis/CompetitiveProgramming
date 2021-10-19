#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }
    bool valid[n][m];
    bool okay[m];
    for (int i = 0; i < m; i++) {
        okay[i] = true;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                valid[i][j] = true;
            } else if (j == 0) {
                valid[i][j] = true;
            } else {
                valid[i][j] = !(v[i - 1][j] == 'X' && v[i][j - 1] == 'X');
            }
            okay[j] = okay[j] && valid[i][j];
        }
    }
    int pref[m];
    pref[0] = 0;
    for (int i = 1; i <= m; i++) {
        pref[i] = pref[i - 1] + !okay[i - 1];
    }
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << "YES\n";
            continue;
        }
        int x = pref[r] - pref[l];
        if (x != 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
