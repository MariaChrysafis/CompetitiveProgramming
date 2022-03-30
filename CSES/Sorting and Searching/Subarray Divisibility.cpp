#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
 
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int64_t> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] < 0) {
            arr[i] = n - (n - arr[i]) % n;
        }
    }
    vector<int64_t> pref = {0};
    for (int i = 0; i < n; i++) {
        pref.push_back(pref.back() + arr[i]);
    }
    vector<int64_t> sm; sm.assign(n, false);
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        pref[i] %= n;
        ans += sm[pref[i] % n];
        sm[pref[i] % n]++;
    }
    cout << ans;
}
