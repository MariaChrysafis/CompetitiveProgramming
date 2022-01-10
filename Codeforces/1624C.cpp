#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

map<int,bool> oc;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        oc.clear();
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            int cur = v[i];
            while (cur > n) {
                cur /= 2;
            }
            while (cur > 0) {
                if (!oc[cur]) {
                    oc[cur] = true;
                    break;
                }
                cur /= 2;
            }
        }
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            if (!oc[i]) {
                cout << "NO\n";
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        cout << "YES\n";
    }
}
