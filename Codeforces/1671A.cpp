#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (s.length() == 1) {
            cout << "NO\n";
            continue;
        } else if (s.length() == 2) {
            if (s == "aa" || s == "bb") {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            bool fine = true;
            for (int i = 0; i < (int)s.length() - 2; i++) {
                if (s[i] != s[i + 1] && s[i + 1] != s[i + 2]) {
                    fine = false;
                }
            }
            if (s[0] != s[1] || s.back() != s[s.length() - 2]) {
                fine = false;
            }
            if (fine) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}
