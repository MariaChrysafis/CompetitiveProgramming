#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int myMax = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i != 0 && arr[i] == arr[i - 1]) {
            continue;
        }
        int prev = i;
        int cntr = 1;
        while (true) {
            if (arr[n - 1] < 2 * arr[prev] - arr[i]) {
                break;
            }
            int l = prev + 1;
            int r = n - 1;
            while (l < r) {
                int m = (l + r) / 2;
                if (arr[m] >= 2 * arr[prev] - arr[i]) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            if (l != r) {
                break;
            }
            prev = l;
            cntr++;
        }
        myMax = max(myMax, cntr);
    }
    cout << n - myMax << '\n';
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
