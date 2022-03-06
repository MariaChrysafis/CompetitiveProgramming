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
    map<int64_t, vector<int64_t>> myMapA, myMapB;
    vector<int64_t> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        myMapA[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        myMapB[b[i]].push_back(i);
    }
    int64_t ans = 0;
    for (auto& p: myMapA) {
        int64_t i = p.first;
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
