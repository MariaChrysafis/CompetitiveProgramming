#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;
void solve () {
    int n;
    cin >> n;
    vector<vector<int>> myMapA(n + 1), myMapB(n + 1);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        myMapA[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        myMapB[b[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < myMapA[i].size(); j++) {
            ans += i * (-myMapA[i][j] + myMapB[i][j]);
        }
    }
    cout << ans << '\n';
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
