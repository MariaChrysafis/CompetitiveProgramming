#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
#include <queue>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int64_t n;
        cin >> n;
        string s;
        cin >> s;
        if (s[0] == 'D') {
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == 'R') s[i] = 'D';
                else s[i] = 'R';
            }
        }
        int64_t r = 1, c = 1;
        for (int i = 0; i < s.length(); i++) {
            r += (s[i] == 'R');
            c += (s[i] == 'D');
        }
        if (r == 1 || c == 1) {
            cout << n << '\n';
            continue;
        }
        int64_t x = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != s[0]) break;
            x++;
        }
        x = x * (n - c);
        cout << n * n - r * c - x + ((int)s.length() + 1) << '\n';
    }
}
