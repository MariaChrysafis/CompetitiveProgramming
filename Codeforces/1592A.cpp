#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")

#define ll long long
using namespace std;
ll ceil(ll a, ll b) {
    return (a + b - 1)/b;
}
void solve () {
    ll n;
    long long h;
    cin >> n >> h;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cout << min(ceil(h, (arr.back() + arr[arr.size() - 2])) * 2, ceil(h - arr.back(), (arr.back() + arr[arr.size() - 2])) * 2 + 1) << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
