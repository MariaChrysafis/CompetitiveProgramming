#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;

int main() {
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
        vector<bool> lm;
        lm.assign(n, false);
        for (int i = 1; i < n - 1; i++) {
            lm[i] = (v[i] > v[i - 1] && v[i] > v[i + 1]);
        }
        int c = 0;
        for (int i = 1; i < n - 1; i++) {
            if (lm[i - 1] && lm[i + 1]) {
                v[i] = max(v[i - 1], v[i + 1]);
                lm[i + 1] = false;
                c++;
            }
        }
        for (int i = 1; i < n - 1; i++) {
            lm[i] = (v[i] > v[i - 1] && v[i] > v[i + 1]);
            if (lm[i]) {
                v[i] = max(v[i - 1], v[i + 1]);
                c++;
            }
        }
        cout << c << '\n';
        for (int i: v) {
            cout << i << ' ';
        }
        cout << '\n';
        cout << '\n';
    }
}
