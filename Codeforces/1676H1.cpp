#include <map>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int arr[n];
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            for (int j = 0; j < i; j++) {
                ans += (int64_t)(arr[i] <= arr[j]);
            }
        }
        cout << ans << '\n';
    }
}
