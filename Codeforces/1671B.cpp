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
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        bool fine = false;
        for (int d = v[0] - 1; d <= v[0] + 1; d++) {
            bool f = true;
            for (int i = 0; i < n; i++) {
                if (abs(d + i - v[i]) > 1) {
                    f = false;
                }
            }
            if (f) {
                fine = true;
            }
        }
        if (!fine) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
