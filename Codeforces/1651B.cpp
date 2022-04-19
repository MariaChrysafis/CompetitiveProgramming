#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> arr(n);
        arr[0] = 1;
        const int MOD = 1e9 + 7;
        for (int i = 1; i < n; i++) {
            arr[i] = arr[i -1 ] * 3;
            arr[i] %= MOD;
        }
        bool fine = true;
        for (int i = 1; i < n; i++) {
            if (arr[i] != arr[i - 1] * 3) {
                fine = false;
            }
        }
        if (!fine) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for (int64_t i: arr) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
