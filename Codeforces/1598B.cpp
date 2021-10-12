#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>

#define ll long long

using namespace std;
void solve () {
    int n;
    cin >> n;
    bool arr[n][5];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> arr[i][j];
        }
    }
    if (n % 2 == 1) {
        cout << "NO\n";
        return;
    }
    for (int g1 = 0; g1 < 5; g1++) {
        for (int g2 = g1 + 1; g2 < 5; g2++) {
            bool fine = true;
            int both = 0;
            int group1 = 0;
            int group2 = 0;
            for (int i = 0; i < n; i++) {
                if (!arr[i][g1] && !arr[i][g2]) {
                    fine = false;
                    break;
                } else if (arr[i][g1] && arr[i][g2]) {
                    both++;
                } else if (arr[i][g1]) {
                    group1++;
                } else if (arr[i][g2]) {
                    group2++;
                }
            }
            if (fine && group1 <= n/2 && group2 <= n/2) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
