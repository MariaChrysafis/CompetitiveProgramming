#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> arr(n);
        int64_t myMin = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            myMin = min(myMin, arr[i]);
        }
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(myMin - arr[i]);
        }
        cout << ans << '\n';
    }
}
