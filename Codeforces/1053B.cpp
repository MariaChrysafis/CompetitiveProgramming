#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = __builtin_popcountll(arr[i]) % 2;
    }
    cout << '\n';
    ll pref[n + 1];
    ll oc[2]; oc[0] = oc[1] = 0;
    pref[0] = 0; oc[0]++;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i - 1];
        pref[i] %= 2; oc[pref[i]]++;
    }
    ll ans = oc[1] * (oc[1] - 1)/2 + oc[0] * (oc[0] - 1)/2;
    for (bool b: a) {
        ans -= !b;
    }
    for (int i = 0; i < n; i++) {
        vector<int> v = {__builtin_popcountll(arr[i])};
        int myMax = v[0];
        int sum = v[0];
        for (int j = i + 1; j < n; j++) {
            if (j - i > 60) break;
            v.push_back(__builtin_popcountll(arr[j]));
            sum += v.back();
            myMax = max(myMax, v.back());
            if (sum < 2 * myMax && sum % 2 == 0) {
                ans--;
            }
        }
    }
    cout << ans;
}
