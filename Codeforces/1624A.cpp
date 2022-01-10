#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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
        int myMax = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            myMax = max(myMax, arr[i]);
        }
        for (int i: arr) {
            ans = max(ans, myMax - i);
        }
        cout << ans << '\n';
    }
}
