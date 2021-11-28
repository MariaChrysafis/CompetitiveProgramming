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
    ll arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll powr = 1;
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        while (arr[i] % 2 == 0) {
            powr *= 2;
            arr[i] /= 2;
        }
    }
    sort(arr, arr + n);
    arr[n - 1] *= powr;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << sum << '\n';
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
