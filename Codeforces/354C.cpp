#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

const ll MOD = 1e9 + 7;

using namespace std;

const int MAX = 1e6 + 10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    map<int,int> oc;
    int myMin = 1e9;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        myMin = min(myMin, arr[i]);
        oc[arr[i]]++;
    }
    vector<int> oc_pref(MAX + 1);
    oc_pref[0] = 0;
    for (int i = 1; i <= MAX; i++) {
        oc_pref[i] = oc_pref[i - 1] + oc[i];
    }
    for (int g = MAX; g >= k + 1; g--) {
        //[g, g + k]
        int ans = 0;
        for (int ind = g; ind < MAX; ind += g) {
            //[ind, ind + k]
            ans += oc_pref[min(ind + k, MAX - 1)] - oc_pref[ind - 1];
            //cout << ind + k << " " << ind - 1 << " " << oc_pref[min(ind + k, MAX - 1)] << " " << oc_pref[ind - 1] << '\n';
        }
        //cout << g << " " << ans << '\n';
        if (ans >= n) {
            cout << g;
            return 0;
        }
    }
    cout << min(myMin, k);
}
