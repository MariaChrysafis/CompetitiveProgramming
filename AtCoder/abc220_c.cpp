#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    long long n;
    cin >> n;
    long long arr[n];
    long long pref[n + 1];
    pref[0] = 0;
    for(int i = 0; i < n; i++) {
         cin >> arr[i];
         pref[i + 1] = pref[i] + arr[i];
    }
    long long x;
    cin >> x;
    long long ans = 0;
    ans += x/pref[n] * n;
    x -= x/pref[n] * pref[n];
    for(int i = 0; i <= n; i++) {
        if(pref[i] > x) {
            cout << ans + i;
            return;
        }
    }
    cout << ans << " " << x << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
