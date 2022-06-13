#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, m;
    cin >> n >> m;
    string arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i += 3) {
        arr[i].assign(m, 'X');
    }
    for (int i = 0; i + 2 < n; i += 3) {
        bool broken = false;
        for (int j = 0; j < m; j++) {
            if (arr[i + 1][j] == 'X') {
                arr[i + 2][j] = 'X', broken = true;
                break;
            }
            if (arr[i + 2][j] == 'X') {
                arr[i + 1][j] = 'X', broken = true;
                break;
            }
        }
        if (!broken) {
            arr[i + 2][0] = arr[i + 1][0] = 'X';
        }
    }
    if (n % 3 == 0) {
        for (int i = 0; i < m; i++) {
            if (arr[n - 1][i] == 'X' || arr[n - 2][i] == 'X') {
                arr[n - 1][i] = arr[n - 2][i] = 'X';
            }
        }
    }
    for (string s: arr) {
        cout << s << '\n';
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
